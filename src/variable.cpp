#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

#include <vector>

variable::variable(const char p_variableCharacter) {
    int variable = 0;
    for ( ; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable] == p_variableCharacter) {
            variableCharacter = s_allVariables[variable];
            break;
        }
    }
    if (variable == s_allVariables.size()) {
        s_allVariables.push_back(p_variableCharacter);
        variableCharacter = s_allVariables.back();
    }

    isVariable = true;
    const_cast<const bool*>(&isVariable);
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

std::vector<const variable*> variable::getVariables() const {
    return {this};
}

bool variable::variableExists(const char p_variableCharacter) {
    for (int variable = 0; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable] == p_variableCharacter)
            return true;
    }
    return false;
}


bool variable::operator==(const variable &p_other) const {
    return variableCharacter == p_other.variableCharacter;
}

bool variable::operator!=(const variable &p_other) const {
    return variableCharacter != p_other.variableCharacter;
}
