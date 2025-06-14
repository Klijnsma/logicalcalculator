#include <stdexcept>

#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

variable::variable(const char p_variableCharacter) : variableCharacter(p_variableCharacter) {
    int variable = 0;
    for ( ; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable]->variableCharacter == p_variableCharacter)
            throw std::invalid_argument("[variable::variable()] A variable with this character has already been initialized.");
    }
    if (variable == s_allVariables.size())
        s_allVariables.push_back(this);

    isVariable = true;
}

bool variable::calculate(const truthTable* p_truthTable, const int row) const {
    return p_truthTable->getTruthValue(this, row);
}

std::string variable::getString() const {
    std::string variableString;
    variableString += variableCharacter;

    return variableString;
}

int variable::getTruthFunctionCount() const {
    return 0;
}

std::vector<variable*> variable::getVariables() const {
    return {variableExists(variableCharacter)};
}

variable* variable::variableExists(const char p_variableCharacter) {
    for (int variable = 0; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable]->variableCharacter == p_variableCharacter)
            return s_allVariables[variable];
    }
    return nullptr;
}