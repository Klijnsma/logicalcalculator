#pragma once

class variable : public symbol {
public:
    variable(char p_variableCharacter, bool p_isPositive);

    bool calculate(const truthTable* p_truthTable, int row) const override;
    std::string getString() const override;
    int getTruthFunctionCount() const override;
    static bool variableExists(char p_variableCharacter);

    bool operator==(const variable& p_other) const;
    bool operator!=(const variable& p_other) const;

    char variableCharacter;

private:
    std::vector<const variable*> getVariables() const override;
};
