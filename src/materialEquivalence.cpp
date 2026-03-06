#include "truthFunction.hpp"
#include "truthTable.hpp"

bool materialEquivalence::calculate(const truthTable* p_truthTable, const int row) const {
    bool value1, value2;

    if (m_items[0]->isVariable) {
        // Get the truth value for the char variables in the given row.
        value1 = p_truthTable->getTruthValue(reinterpret_cast<const variable*>(m_items[0]), row) == m_items[0]->isPositive;
    }
    else {
        // Make sure any nested truthFunctions are calculated first.
        value1 = m_items[0]->calculate(p_truthTable, row);
    }

    if (m_items[1]->isVariable) {
        // Get the truth value for the char variables in the given row.
        value2 = p_truthTable->getTruthValue(reinterpret_cast<const variable*>(m_items[1]), row) == m_items[1]->isPositive;
    }
    else {
        // Make sure any nested truthFunctions are calculated first.
        value2 = m_items[1]->calculate(p_truthTable, row);
    }

    return (value1 == value2) == isPositive;
}

constexpr std::string materialEquivalence::getOperator() const { return " ↔ "; }
