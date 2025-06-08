// #include <algorithm>

#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

variable::variable(char p_variableCharacter) : variableCharacter(p_variableCharacter) {
    int variable = 0;
    for ( ; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable]->variableCharacter == p_variableCharacter)
            // this = s_allVariables[variable];
            return;
    }
    if (variable == s_allVariables.size())
        s_allVariables.push_back(this);

    // variableCharacter = p_variableCharacter;

    isVariable = true;
}

bool variable::calculate(truthTable* p_truthTable, int row) const {
    return p_truthTable->getTruthValue(this, row);
}

int variable::getTruthFunctionCount() const {
    return 0;
}

std::string variable::getString() const {
    std::string variableString;
    variableString += variableCharacter;

    return variableString;
}
