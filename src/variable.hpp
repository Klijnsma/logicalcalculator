#pragma once

#include "truthFunction.hpp"
#include "truthTable.hpp"

class variable : public symbol {
public:
    variable(char p_variableCharacter) {
        if (std::find(s_allVariables.begin(), s_allVariables.end(), this) == s_allVariables.end())
            s_allVariables.push_back(this);

        variableCharacter = p_variableCharacter;
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        return p_truthTable->getTruthValue(this, row);
    };

    std::string getString() const override {
        std::string variableString;
        variableString += variableCharacter;

        return variableString;
    }

    int getTruthFunctionCount() const override {
        return 0;
    }

    char variableCharacter;
    const bool isVariable = true;
};
