#pragma once

class symbol;
class variable;

class truthTable {
public:
    truthTable(const std::vector<symbol*>& p_premises, const symbol* p_conclusion);
    ~truthTable();

    bool getTruthValue(const variable* variable, int row) const;
    void print() const;

private:
    int columns;
    int rows;
    int variableCount;
    int premiseCount;

    std::vector<symbol*> premises;
    const symbol* conclusion;
    std::vector<const variable*> m_variables;

    // Storage for the actual truth table truth values.
    bool** variableCombinations;
    bool** premiseResults;
    bool* combinedPremiseResults;
    bool* conclusionTruth;
    bool* conclusionFollowsFromPremises;

    bool validity;
};
