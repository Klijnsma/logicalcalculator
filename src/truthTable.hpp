#pragma once

class symbol;
class variable;

class truthTable {
public:
    truthTable(const std::vector<symbol*>& p_premises, const symbol* p_conclusion);
    ~truthTable();

    bool getTruthValue(const variable* p_variable, const int p_row) const;
    void print() const;

    bool validity;

private:
    static void calculatePremise(const truthTable* p_truthTable, const unsigned int p_premiseNumber);

    void fillColumnBlock(const unsigned int p_variable, const unsigned int p_firstRow, const unsigned int p_blockSize, const bool p_truthValue) const;

    unsigned int columns;
    unsigned int rows;
    unsigned int variableCount;
    unsigned int premiseCount;

    std::vector<symbol*> m_premises;
    const symbol* m_conclusion;
    std::vector<const variable*> m_variables;

    // Storage for the actual truth table truth values.
    bool* m_table;
};
