#include <algorithm>
#include <cmath>
#include <future>
#include <iostream>
#include <stdexcept>

#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

truthTable::truthTable(const std::vector<symbol*>& p_premises, const symbol* p_conclusion) {

    // Add the pointers to variables from p_premises to m_variables, avoiding any duplicates.
    for (int premise = 0; premise < p_premises.size(); premise++) {
        const std::vector<const variable*> premiseVariables = p_premises[premise]->getVariables();

        // For every variable in premiseVariables, cycle through m_variables and check whether they are already stored in there.
        for (int currentPremiseVariable = 0; currentPremiseVariable < premiseVariables.size(); currentPremiseVariable++) {
            bool foundVariable = false;

            for (int truthTableVariable = 0; truthTableVariable < m_variables.size(); truthTableVariable++) {
                if (*premiseVariables[currentPremiseVariable] == *m_variables[truthTableVariable]) {
                    foundVariable = true;
                    break;
                }
            }

            if (!foundVariable)
                m_variables.push_back(premiseVariables[currentPremiseVariable]);
        }
    }

    // Do the same thing with p_conclusion
    {
        const std::vector<const variable*> conclusionVariables = p_conclusion->getVariables();

        for (int currentConclusionVariable = 0; currentConclusionVariable < conclusionVariables.size(); currentConclusionVariable++) {
            bool foundVariable = false;

            for (int truthTableVariable = 0; truthTableVariable < m_variables.size(); truthTableVariable++) {
                if (*conclusionVariables[currentConclusionVariable] == *m_variables[truthTableVariable]) {
                    foundVariable = true;
                    break;
                }
            }

            if (!foundVariable)
                m_variables.push_back(conclusionVariables[currentConclusionVariable]);
        }
    }

    variableCount = m_variables.size();
    premiseCount = p_premises.size();
    columns = variableCount + premiseCount + 3; // 3 columns total for combined premises, conclusion and validity.
    rows = std::pow(2, variableCount);

    m_premises = p_premises;
    m_conclusion = p_conclusion;

    m_table = new bool[columns * rows];

    // Calculate every possible truth value combination for the given amount of variables and store them in the first variableCount columns of m_table.
    for (int variable = 0; variable < variableCount; variable++) {
        // For the variables each column is divided into blocks (consecutive rows with identical values)
        const int blockSize = rows / std::pow(2, variable + 1);
        bool truthValue = true;

        for (int block = 0; block < rows / blockSize; block++) {
            // Alternate the boolean value for the variable being worked on.
            fillColumnBlock(variable, block * blockSize, blockSize, truthValue);
            truthValue = !truthValue;
        }
    }

    std::future<void>* premiseCalculations = new std::future<void>[premiseCount];

    // Calculate the results of the premises in each row.
    for (unsigned int currentPremise = 0; currentPremise < premiseCount; currentPremise++) {
        premiseCalculations[currentPremise] = std::async(std::launch::async, calculatePremise, this, currentPremise);
    }

    for (unsigned int currentPremise = 0; currentPremise < premiseCount; currentPremise++) {
        premiseCalculations[currentPremise].wait();
    }

    delete[] premiseCalculations;

    int followingConclusions = 0;

    // Calculate for each row whether all premises are true, whether the conclusion is true
    // and whether the conclusion is materially implied by the premises.
    for (int currentRow = 0; currentRow < rows; currentRow++) {

        // Combined premises
        int currentPremise = 0;
        for (; currentPremise < premiseCount; currentPremise++) {
            if (!m_table[(currentPremise + variableCount) + (currentRow * columns)]) {
                m_table[(variableCount + premiseCount) + (currentRow * columns)] = false;
               break;
            }
        }
        if (currentPremise == premiseCount)
            m_table[(variableCount + premiseCount) + (currentRow * columns)] = true;

        // Conclusion
        m_table[(variableCount + premiseCount + 1) + (currentRow * columns)] = p_conclusion->calculate(this, currentRow);

        // Validity
        m_table[(variableCount + premiseCount + 2) + (currentRow * columns)] = !(m_table[(variableCount + premiseCount) + (currentRow * columns)] && !m_table[(variableCount + premiseCount + 1) + (currentRow * columns)]);
        if (m_table[(variableCount + premiseCount + 2) + (currentRow * columns)])
            followingConclusions++;

    }

    if (followingConclusions == rows) {
        validity = true;
        return;
    }
    validity = false;
    validity = const_cast<const bool&>(validity);
}

truthTable::~truthTable() {
    delete[] m_table;
}

void truthTable::calculatePremise(const truthTable* p_truthTable, const unsigned int p_premiseNumber) {
    for (int currentRow = 0; currentRow < p_truthTable->rows; currentRow++) {
        // Dealing with truthFunctions inside truthFunctions is done by the calculate() function.
        p_truthTable->m_table[(p_premiseNumber + p_truthTable->variableCount) + (currentRow * p_truthTable->columns)] = p_truthTable->m_premises[p_premiseNumber]->calculate(p_truthTable, currentRow);
    }
}

void truthTable::fillColumnBlock(const unsigned int p_variable, const unsigned int p_firstRow, const unsigned int p_blockSize, const bool p_truthValue) const {
    for (int currentRow = p_firstRow; currentRow < p_firstRow + p_blockSize; currentRow++) {
        m_table[p_variable + currentRow * columns] = p_truthValue;
    }
}

bool truthTable::getTruthValue(const variable* p_variable, const int p_row) const {
    for (int variableNumber = 0; variableNumber < variableCount; variableNumber++) {
        if (m_variables[variableNumber]->variableCharacter == p_variable->variableCharacter) {
            return m_table[variableNumber + p_row * columns];
        }
    }

    throw std::invalid_argument("[truthTable::getTruthValue()]: Variable not found in truthTable.");
}

void truthTable::print() const {

    // ----------------------------------------------------------------------------------
    // Row 1

    for (int var = 0; var < m_variables.size(); var++) {
        std::cout << ' ' << m_variables[var]->getString();
    }

    std::string combinedPremisesString = "";

    for (int prem = 0; prem < m_premises.size(); prem++) {
        std::cout << '\t' << m_premises[prem]->getString();

        if (prem > 0)
            combinedPremisesString += " ∧ ";

        if (m_premises[prem]->isVariable)
            combinedPremisesString += m_premises[prem]->getString();
        else
            combinedPremisesString += '(' + m_premises[prem]->getString() + ')';
    }

    std::cout << '\t' << m_conclusion->getString() << ' ';
    if (m_premises.size() > 1 || !m_premises[0]->isVariable)
        combinedPremisesString = '(' + combinedPremisesString + ')';
    std::cout << '\t' << combinedPremisesString << " → " << m_conclusion->getString();

    std::cout << std::endl;

    // ----------------------------------------------------------------------------------
    // Data fields

    // Cycle through the rows
    for (int row = 0; row < rows; row++) {
        // Cycle through variables
        for (int var = 0; var < m_variables.size(); var++)
            std::cout << ' ' << m_table[var + row * columns];

        // Cycle through premises
        for (int prem = 0; prem < m_premises.size(); prem++)
            std::cout << '\t' << m_table[(m_variables.size() + prem) + row * columns];

        // Conclusion and validity columns
        std::cout << '\t' << m_table[m_variables.size() + m_premises.size() + 1 + row * columns];
        std::cout << '\t' << m_table[m_variables.size() + m_premises.size() + 2 + row * columns];

        std::cout << std::endl;
    }
}
