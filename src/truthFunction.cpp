#include "truthFunction.hpp"

truthFunction::truthFunction(symbol* p_item1, symbol* p_item2) {
    items.push_back(p_item1);
    items.push_back(p_item2);

    isVariable = false;
    isVariable = const_cast<const bool&>(isVariable);
}

int truthFunction::getTruthFunctionCount() const {
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

std::vector<const variable*> truthFunction::getVariables() const {
    std::vector<const variable*> foundVariables;

    if (items[0]->isVariable)
        foundVariables.push_back(reinterpret_cast<variable*>(items[0]));
    else {
        std::vector<const variable*> singleParametersVariables = reinterpret_cast<truthFunction*>(items[0])->getVariables();
        foundVariables.reserve(singleParametersVariables.size());
        foundVariables.insert(foundVariables.end(), singleParametersVariables.begin(), singleParametersVariables.end());
    }

    if (items[1]->isVariable)
        foundVariables.push_back(reinterpret_cast<variable*>(items[1]));
    else {
        std::vector<const variable*> singleParametersVariables = reinterpret_cast<truthFunction*>(items[1])->getVariables();
        foundVariables.reserve(singleParametersVariables.size());
        foundVariables.insert(foundVariables.end(), singleParametersVariables.begin(), singleParametersVariables.end());
    }

    return foundVariables;
}

const symbol* truthFunction::operator[](const int p_index) const {
    return items[p_index];
}

truthFunction::~truthFunction() {
    delete items[0];
    delete items[1];
}
