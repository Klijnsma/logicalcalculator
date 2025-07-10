#include "truthFunction.hpp"
#include "truthTable.hpp"

std::string materialEquivalence::getString() const {
    std::string premiseString;

    if (m_items[0]->isVariable)
        premiseString = m_items[0]->getString();
    else
        premiseString = '(' + m_items[0]->getString() + ')';

    premiseString += " ↔ ";

    if (m_items[1]->isVariable)
        premiseString += m_items[1]->getString();
    else
        premiseString += '(' + m_items[1]->getString() + ')';

    if (!isPositive) {
        premiseString.insert(0, "!(");
        premiseString += ')';
    }

    return premiseString;
}

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
