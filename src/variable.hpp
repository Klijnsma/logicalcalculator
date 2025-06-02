#pragma once

#include "truthFunction.hpp"
#include "truthTable.hpp"

class variable : public truthFunction {
public:
    variable(char p_variableCharacter) {
        variableCharacter = p_variableCharacter;
    }

    bool calculate(truthTable* p_truthTable, int row) const {
        return p_truthTable->getTruthValue(variableCharacter, row);
    };

    std::string getString() {
        std::string variableString;
        variableString += variableCharacter;

        return variableString;
    }

    char variableCharacter;
};
