#pragma once

#include "truthFunction.hpp"
#include "truthTable.hpp"

class variable : public truthFunction {
public:
    variable(char p_variableCharacter) {
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_variableCharacter) == s_allVariables.end())
            s_allVariables.push_back(p_variableCharacter);

        variableCharacter = p_variableCharacter;

        items.emplace_back(p_variableCharacter);
        items.emplace_back(p_variableCharacter);
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        return p_truthTable->getTruthValue(variableCharacter, row);
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
private:
    inline static int defaultTruthFunctions = 0;
};
