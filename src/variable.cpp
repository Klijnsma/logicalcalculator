#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

variable::variable(char p_variableCharacter) {
    if (std::find(s_allVariables.begin(), s_allVariables.end(), this) == s_allVariables.end())
        s_allVariables.push_back(this);

    variableCharacter = p_variableCharacter;

    isVariable = true;
}

bool variable::calculate(truthTable* p_truthTable, int row) const {
    return p_truthTable->getTruthValue(this, row);
};

std::string variable::getString() const {
    std::string variableString;
    variableString += variableCharacter;

    return variableString;
}

int variable::getTruthFunctionCount() const {
    return 0;
}
