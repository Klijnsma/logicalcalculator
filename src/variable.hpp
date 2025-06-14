#pragma once

class variable : public symbol {
public:
    variable(char p_variableCharacter);

    bool calculate(truthTable* p_truthTable, int row) const override;
    std::string getString() const override;
    int getTruthFunctionCount() const override;
    std::vector<variable*> getVariables() const override;
    static variable* variableExists(char p_variableCharacter);

    const char variableCharacter;
};
