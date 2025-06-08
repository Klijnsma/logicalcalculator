#pragma once

class variable : public symbol {
public:
    variable(char p_variableCharacter);

    bool calculate(truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
    std::string getString() const override;

    const char variableCharacter;
};
