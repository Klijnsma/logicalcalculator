#include "truthFunction.hpp"

std::string conjunction::getString() const {
    std::string premiseString;

    if (items[0]->isVariable)
        premiseString = items[0]->getString();
    else
        premiseString = '(' + items[0]->getString() + ')';

    premiseString += " ∧ ";

    if (items[1]->isVariable)
        premiseString += items[1]->getString();
    else
        premiseString += '(' + items[1]->getString() + ')';

    return premiseString;
}

bool conjunction::calculate(truthTable* p_truthTable, int row) const {
    bool value1, value2;

    if (items[0]->isVariable)
        // Get the truth value for the char variables in the given row.
            value1 = p_truthTable->getTruthValue(reinterpret_cast<variable*>(items[0]), row);
    else
        // Make sure any nested truthFunctions are calculated first.
            value1 = items[0]->calculate(p_truthTable, row);

    if (items[1]->isVariable)
        // Get the truth value for the char variables in the given row.
            value2 = p_truthTable->getTruthValue(reinterpret_cast<variable*>(items[1]), row);
    else
        // Make sure any nested truthFunctions are calculated first.
            value2 = items[1]->calculate(p_truthTable, row);

    return value1 && value2;
}

int conjunction::getTruthFunctionCount() const {
    int truthFunctions = 1;

    if (!items[0]->isVariable) {
        truthFunctions++;
        truthFunctions += items[0]->getTruthFunctionCount();
    }
    if (!items[1]->isVariable) {
        truthFunctions++;
        truthFunctions += items[1]->getTruthFunctionCount();
    }

    return truthFunctions;
}
