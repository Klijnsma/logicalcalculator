#pragma once

#include <cmath>
// #include <cstring>

// #include <iostream>

#include "logicalOperations.hpp"

class truthTable {
public:
    truthTable(std::vector<std::vector<truthFunction>> premises, std::vector<truthFunction> conclusion) {
        variableCount = truthFunction::s_allVariables.size();
        columns = variableCount + premises.size();
        rows = std::pow(2, variableCount);

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

        // for (int currentPremise = 0; currentPremise < premises.size(); currentPremise++) {
            // for (int currentTruthFunction = 0; currentTruthFunction < premises[currentPremise].size(); currentTruthFunction++) {
            // }
        // }
    }

    bool getTruthValue(char variable, int row) {
        int variableNumber = std::distance(truthFunction::s_allVariables.begin(),
                             std::find(truthFunction::s_allVariables.begin(), truthFunction::s_allVariables.end(), variable));

        if (std::find(truthFunction::s_allVariables.begin(), truthFunction::s_allVariables.end(), variable)
            != truthFunction::s_allVariables.end()) {

            return variableCombinations[variableNumber][row];
        }

        // TODO: make this better.
        return false;
    }

    ~truthTable() {
        for (int variable = 0; variable < variableCount; variable++) {
            delete[] variableCombinations[variable];
        }
        delete[] variableCombinations;
    }

    int columns;
    int rows;
    int variableCount;

    // 2D array to contain all possible truth value combinations of the variables in truthFunction::s_allVariables.
    bool** variableCombinations;
};
