#include <stdexcept>

#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

variable::variable(char p_variableCharacter) : variableCharacter(p_variableCharacter) {
    int variable = 0;
    for ( ; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable]->variableCharacter == p_variableCharacter)
            throw std::invalid_argument("[variable::variable()] A variable with this character has already been initialized.");
    }
    if (variable == s_allVariables.size())
        s_allVariables.push_back(this);

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
