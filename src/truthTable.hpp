#pragma once

#include <cmath>
#include <stdexcept>

#include "truthFunction.hpp"

class truthTable {
public:
    truthTable(const std::vector<const truthFunction*>* p_premises, const truthFunction* p_conclusion) {
        variableCount = truthFunction::s_allVariables.size();
        columns = variableCount + p_premises->size() + 3;
        rows = std::pow(2, variableCount);
        premiseCount = p_premises->size();

        premises = p_premises;
        conclusion = p_conclusion;

        variableCombinations = new bool*[variableCount];

        // Calculate every possible truth value combination for the given amount of variables and store them in possibleTruthValues.
        for (int variable = 0; variable < variableCount; variable++) {
            variableCombinations[variable] = new bool[rows];
            int blockSize = rows / std::pow(2, variable + 1);
            bool truthValue = true;

            for (int block = 0; block < rows / blockSize; block++) {
                // Alternate the boolean value for the variable being worked on.
                std::fill(&variableCombinations[variable][block * blockSize],
                          &variableCombinations[variable][block * blockSize + blockSize], truthValue);
                truthValue = !truthValue;
            }
        }

        premiseResults = new bool*[p_premises->size()];

        // Calculate the results of the premises in each row.
        for (int currentPremise = 0; currentPremise < p_premises->size(); currentPremise++) {
            premiseResults[currentPremise] = new bool[rows];

            for (int currentRow = 0; currentRow < rows; currentRow++) {
                // Dealing with truthFunctions inside truthFunctions is dealt with by the calculate() 4function.
                premiseResults[currentPremise][currentRow] = (*p_premises)[currentPremise]->calculate(this, currentRow);
            }
        }

        combinedPremiseResults = new bool[rows];
        conclusionTruth = new bool[rows];
        conclusionFollowsFromPremises = new bool[rows];

        int followingConclusions = 0;

        // Calculate for each row whether all premises are true, whether the conclusion is true
        // and whether the conclusion is materially implied by the premises.
        for (int currentRow = 0; currentRow < rows; currentRow++) {
            int currentPremise = 0;

            for (; currentPremise < p_premises->size(); currentPremise++) {
                if (!premiseResults[currentPremise][currentRow]) {
                    combinedPremiseResults[currentRow] = false;
                   break;
                }
            }
            if (currentPremise == p_premises->size())
                combinedPremiseResults[currentRow] = true;

            conclusionTruth[currentRow] = p_conclusion->calculate(this, currentRow);

            conclusionFollowsFromPremises[currentRow] = !(combinedPremiseResults[currentRow] && !conclusionTruth[currentRow]);
            if (conclusionFollowsFromPremises[currentRow])
                followingConclusions++;
        }

        if (followingConclusions == rows) {
            validity = true;
            return;
        }
        validity = false;
    }

    bool getTruthValue(char variable, int row) {
        int variableNumber = std::distance(truthFunction::s_allVariables.begin(),
                                           std::find(truthFunction::s_allVariables.begin(), truthFunction::s_allVariables.end(), variable));

        if (std::find(truthFunction::s_allVariables.begin(), truthFunction::s_allVariables.end(), variable)
            != truthFunction::s_allVariables.end()) {

            return variableCombinations[variableNumber][row];
        }

        throw std::invalid_argument("[truthTable::getTruthValue()]: Variable not found in truthFunction::s_allVariables");
    }

    void print() {
        int columnSize[premiseCount + 2]; // Only premises, combined premises and conclusion rows need column size to be remembered.
        // columnSize does not include the size of the " | " seperator

        // Print the variables as chars.
        for (int variable = 0; variable < variableCount; variable++) {
            std::cout << truthFunction::s_allVariables[variable] << " | ";
        }

        std::string combinedPremisesString = "(";
        int operators = 0;

        // Print the premises as strings and begin preparing for printing combinedPremises.
        for (int premise = 0; premise < premiseCount; premise++) {
            std::string currentPremiseString = (*premises)[premise]->getString();

            std::cout << currentPremiseString << " | ";
            columnSize[premise] = currentPremiseString.length() - (*premises)[premise]->getTruthFunctionCount();

            combinedPremisesString += '(' + (*premises)[premise]->getString() + ") ∧ ";
            operators += (*premises)[premise]->getTruthFunctionCount();
        }

        // Remove the trailing conjunction operator.
        combinedPremisesString = combinedPremisesString.substr(0, combinedPremisesString.length() - 6);
        combinedPremisesString += ')';
        std::cout << combinedPremisesString << " | ";

        columnSize[premiseCount] = 2; // 2 for outermost parentheses
        columnSize[premiseCount] += combinedPremisesString.length() - 6 - operators;

        std::string conclusionString = conclusion->getString();
        std::cout << conclusionString << " | ";

        columnSize[premiseCount + 1] = conclusionString.length() - conclusion->getTruthFunctionCount();

        std::cout << combinedPremisesString << " → (" << conclusionString << ")\n";

        // Print the truth values
        for (int currentRow = 0; currentRow < rows; currentRow++) {
            for (int variable = 0; variable < variableCount; variable++) {
                std::cout << variableCombinations[variable][currentRow] << " | ";
            }
            for (int premise = 0; premise < premiseCount; premise++) {
                std::cout << premiseResults[premise][currentRow] << std::string(columnSize[premise] - 2, ' ') << " | ";
            }
            std::cout << combinedPremiseResults[currentRow] << std::string(columnSize[premiseCount] - 1, ' ') << " | ";
            std::cout << conclusionTruth[currentRow] << std::string(columnSize[premiseCount + 1] - 2, ' ') << " | ";
            std::cout << conclusionFollowsFromPremises[currentRow] << '\n';
        }
    }

    ~truthTable() {
        for (int variable = 0; variable < variableCount; variable++) {
            delete[] variableCombinations[variable];
        }
        delete[] variableCombinations;

        for (int premise = 0; premise < premiseCount; premise++) {
            delete[] premiseResults[premise];
        }
        delete[] premiseResults;

        delete[] combinedPremiseResults;
        delete[] conclusionTruth;
        delete[] conclusionFollowsFromPremises;
    }

    int columns;
    int rows;
    int variableCount;
    int premiseCount;

    const std::vector<const truthFunction*>* premises;
    const truthFunction* conclusion;

    // Storage for the actual truth table.
    bool** variableCombinations;
    bool** premiseResults;
    bool* combinedPremiseResults;
    bool* conclusionTruth;
    bool* conclusionFollowsFromPremises;

    bool validity;
};
