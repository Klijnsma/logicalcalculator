#include "truthFunction.hpp"
#include "truthTable.hpp"

std::string inclusiveDisjunction::getString() const {
    std::string premiseString;

    if (items[0]->isVariable)
        premiseString = items[0]->getString();
    else
        premiseString = '(' + items[0]->getString() + ')';

    premiseString += " ∨ ";

    if (items[1]->isVariable)
        premiseString += items[1]->getString();
    else
        premiseString += '(' + items[1]->getString() + ')';

    if (!isPositive) {
        premiseString.insert(0, "!(");
        premiseString += ')';
    }

    return premiseString;
}

bool inclusiveDisjunction::calculate(const truthTable* p_truthTable, const int row) const {
    bool value1, value2;

    if (items[0]->isVariable) {
        // Get the truth value for the char variables in the given row.
        value1 = p_truthTable->getTruthValue(reinterpret_cast<const variable*>(items[0]), row) == items[0]->isPositive;
    }
    else {
        // Make sure any nested truthFunctions are calculated first.
        value1 = items[0]->calculate(p_truthTable, row);
    }

    if (items[1]->isVariable) {
        // Get the truth value for the char variables in the given row.
        value2 = p_truthTable->getTruthValue(reinterpret_cast<const variable*>(items[1]), row) == items[1]->isPositive;
    }
    else {
        // Make sure any nested truthFunctions are calculated first.
        value2 = items[1]->calculate(p_truthTable, row);
    }

    return (value1 || value2) == isPositive;
}
