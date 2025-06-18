#include <algorithm>
#include <cmath>
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
    columns = variableCount + p_premises.size() + 3;
    rows = std::pow(2, variableCount);
    premiseCount = p_premises.size();

    m_premises = p_premises;
    m_conclusion = p_conclusion;

    m_variableColumns = new bool*[variableCount];

    // Calculate every possible truth value combination for the given amount of variables and store them in possibleTruthValues.
    for (int variable = 0; variable < variableCount; variable++) {
        m_variableColumns[variable] = new bool[rows];
        const int blockSize = rows / std::pow(2, variable + 1);
        bool truthValue = true;

        for (int block = 0; block < rows / blockSize; block++) {
            // Alternate the boolean value for the variable being worked on.
            std::fill(&m_variableColumns[variable][block * blockSize],
                      &m_variableColumns[variable][block * blockSize + blockSize], truthValue);
            truthValue = !truthValue;
        }
    }

    m_premiseColumns = new bool*[p_premises.size()];

    // Calculate the results of the premises in each row.
    for (int currentPremise = 0; currentPremise < p_premises.size(); currentPremise++) {
        m_premiseColumns[currentPremise] = new bool[rows];

        for (int currentRow = 0; currentRow < rows; currentRow++) {
            // Dealing with truthFunctions inside truthFunctions is dealt with by the calculate() 4function.
            m_premiseColumns[currentPremise][currentRow] = p_premises[currentPremise]->calculate(this, currentRow);
        }
    }

    m_combinedPremisesColumn = new bool[rows];
    m_conclusionColumn = new bool[rows];
    m_validityColumn = new bool[rows];

    int followingConclusions = 0;

    // Calculate for each row whether all premises are true, whether the conclusion is true
    // and whether the conclusion is materially implied by the premises.
    for (int currentRow = 0; currentRow < rows; currentRow++) {
        int currentPremise = 0;

        for (; currentPremise < p_premises.size(); currentPremise++) {
            if (!m_premiseColumns[currentPremise][currentRow]) {
                m_combinedPremisesColumn[currentRow] = false;
               break;
            }
        }
        if (currentPremise == p_premises.size())
            m_combinedPremisesColumn[currentRow] = true;

        m_conclusionColumn[currentRow] = p_conclusion->calculate(this, currentRow);

        m_validityColumn[currentRow] = !(m_combinedPremisesColumn[currentRow] && !m_conclusionColumn[currentRow]);
        if (m_validityColumn[currentRow])
            followingConclusions++;
    }

    if (followingConclusions == rows) {
        validity = true;
        return;
    }
    validity = false;
}

bool truthTable::getTruthValue(const variable* variable, const int row) const {
    for (int variableNumber = 0; variableNumber < variableCount; variableNumber++) {
        if (*m_variables[variableNumber] == *variable) {
            return m_variableColumns[variableNumber][row];
        }
    }

    throw std::invalid_argument("[truthTable::getTruthValue()]: Variable not found in truthTable.");
}

void truthTable::print() const {
    int columnSizeDiff[premiseCount + 2]; // Only premises, combined premises and conclusion rows need column size to be remembered.
    // column Size does not include the size of the " | " seperator

    // Print the variables as chars.
    for (int variable = 0; variable < variableCount; variable++) {
        std::cout << (m_variables[variable]->getString()) << " | ";
    }

    std::string combinedPremisesString;
    columnSizeDiff[premiseCount] = 0;
    int mereVariables = 0;
    int truthFunctions = 0;

    // Print the premises as strings and begin preparing for printing combinedPremises.
    for (int premise = 0; premise < premiseCount; premise++) {
        std::string currentPremiseString = m_premises[premise]->getString();
        std::cout << currentPremiseString << " | ";
        int currentPremiseTruthFunctions = m_premises[premise]->getTruthFunctionCount();
        columnSizeDiff[premise] = currentPremiseString.length() - 2 - currentPremiseTruthFunctions;

        // Do different things based on whether premise is a variable or an actual truth function.
        if (!m_premises[premise]->isVariable) {
            combinedPremisesString += '(' + currentPremiseString + ')';
            columnSizeDiff[premiseCount] += currentPremiseString.length() - currentPremiseTruthFunctions + 1;
            truthFunctions += currentPremiseTruthFunctions;
        }
        else {
            combinedPremisesString += currentPremiseString;
            columnSizeDiff[premiseCount] += currentPremiseString.length();
            mereVariables++;
        }
        combinedPremisesString += " ∧ ";
        columnSizeDiff[premiseCount] += 3;
    }

    // Remove trailing " ∧ ".
    combinedPremisesString = combinedPremisesString.substr(0, combinedPremisesString.length() - 5);
    columnSizeDiff[premiseCount] -= 3;

    if (premiseCount > 2) {
        combinedPremisesString.insert(0, 1, '(');
        combinedPremisesString += ')';
        columnSizeDiff[premiseCount] += 2;
        if (mereVariables > 1) {
            columnSizeDiff[premiseCount]--;
        }
        if (truthFunctions > 2) {
            columnSizeDiff[premiseCount]--;
        }
    }
    else {
        columnSizeDiff[premiseCount]--;
    }

    std::cout << combinedPremisesString << " | ";

    std::string conclusionString = m_conclusion->getString();
    std::cout << conclusionString << " | ";
    columnSizeDiff[premiseCount + 1] = conclusionString.length() - 2 - m_conclusion->getTruthFunctionCount();

    // Print validity column truth function.
    std::cout << combinedPremisesString << " → ";
    if (m_conclusion->isVariable)
        std::cout << conclusionString << '\n';
    else
        std::cout << "(" << conclusionString << ")\n";

    // Print the truth values
    for (int currentRow = 0; currentRow < rows; currentRow++) {
        for (int variable = 0; variable < variableCount; variable++) {
            std::cout << m_variableColumns[variable][currentRow] << " | ";
        }
        for (int premise = 0; premise < premiseCount; premise++) {
            std::cout << m_premiseColumns[premise][currentRow] << std::string(std::max(columnSizeDiff[premise], 0), ' ') << " | ";
        }
        std::cout << m_combinedPremisesColumn[currentRow] << std::string(std::max(columnSizeDiff[premiseCount], 0), ' ') << " | ";
        std::cout << m_conclusionColumn[currentRow] << std::string(std::max(columnSizeDiff[premiseCount + 1], 0), ' ') << " | ";
        std::cout << m_validityColumn[currentRow] << '\n';
    }
}

truthTable::~truthTable() {
    for (int variable = 0; variable < variableCount; variable++) {
        delete[] m_variableColumns[variable];
    }
    delete[] m_variableColumns;

    for (int premise = 0; premise < premiseCount; premise++) {
        delete[] m_premiseColumns[premise];
    }
    delete[] m_premiseColumns;

    delete[] m_combinedPremisesColumn;
    delete[] m_conclusionColumn;
    delete[] m_validityColumn;
}
