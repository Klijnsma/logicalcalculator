#include <cmath>

#include "logicalOperations.hpp"

bool masterCalculate(std::vector<std::vector<truthFunction>> premises, std::vector<truthFunction> conclusion) {
    int variableCount = truthFunction::s_allVariables.size();
    int possibleCombinations = std::pow(2, variableCount);
    bool possibleTruthValues[variableCount][possibleCombinations];

    // Calculate every possible truth value combination for the given amount of variables and store them in possibleTruthValues.
    for (int variable = 0; variable < variableCount; variable++) {
        int blockSize = possibleCombinations / std::pow(2, (variable + 1));
        bool truthValue = true;

        for (int block = 0; block < possibleCombinations / blockSize; block++) {
            // Alternate the boolean value for the variable being worked on.
            std::fill(possibleTruthValues[variable][block * blockSize],
                      possibleTruthValues[variable][block * blockSize + blockSize], truthValue);
            truthValue = !truthValue;
        }
    }
}
