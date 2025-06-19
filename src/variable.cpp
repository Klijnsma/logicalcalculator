#include "symbol.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

variable::variable(const char p_variableCharacter, bool positivity) {
    int variable = 0;
    for ( ; variable < s_allVariables.size(); variable++) {
        if (s_allVariables[variable] == p_variableCharacter) {
            variableCharacter = s_allVariables[variable];
            variableCharacter = const_cast<const char&>(variableCharacter);
            break;
        }
    }
    if (variable == s_allVariables.size()) { // A variable with the same character was not found in s_allVariables.
        s_allVariables.push_back(p_variableCharacter);
        variableCharacter = s_allVariables.back();
        variableCharacter = const_cast<const char&>(variableCharacter);
    }

    isPositive = positivity;
    isPositive = const_cast<const bool&>(isPositive);

    isVariable = true;
    isVariable = const_cast<const bool&>(isVariable);
}

bool variable::calculate(const truthTable* p_truthTable, const int row) const {
    return (p_truthTable->getTruthValue(this, row)) == isPositive;
}

std::string variable::getString() const {
    std::string variableString;

    if (!isPositive)
        variableString += '!';
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
