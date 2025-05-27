#include <math.h>

#include "logicalOperations.hpp"

bool masterCalculate(std::vector<std::vector<truthFunction>> premises, std::vector<truthFunction> conclusion) {
    int variableCount = truthFunction::s_allVariables.size();
    int possibleCombinations = std::pow(2, variableCount);

    bool possibleTruthValues[variableCount][possibleCombinations];
}
