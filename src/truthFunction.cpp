#include "truthFunction.hpp"

truthFunction::truthFunction(symbol* p_item1, symbol* p_item2, const bool p_isPositive) {
    m_items.push_back(p_item1);
    m_items.push_back(p_item2);

    isPositive = p_isPositive;
    isPositive = const_cast<const bool&>(isPositive);

    isVariable = false;
    isVariable = const_cast<const bool&>(isVariable);
}

int truthFunction::getTruthFunctionCount() const {
    int truthFunctions = 1;

    if (!m_items[0]->isVariable)
        truthFunctions += m_items[0]->getTruthFunctionCount();
    if (!m_items[1]->isVariable)
        truthFunctions += m_items[1]->getTruthFunctionCount();

    return truthFunctions;
}

std::vector<const variable*> truthFunction::getVariables() const {
    std::vector<const variable*> foundVariables;

    if (m_items[0]->isVariable)
        foundVariables.push_back(reinterpret_cast<variable*>(m_items[0]));
    else {
        std::vector<const variable*> singleParametersVariables = reinterpret_cast<truthFunction*>(m_items[0])->getVariables();
        foundVariables.reserve(singleParametersVariables.size());
        foundVariables.insert(foundVariables.end(), singleParametersVariables.begin(), singleParametersVariables.end());
    }

    if (m_items[1]->isVariable)
        foundVariables.push_back(reinterpret_cast<variable*>(m_items[1]));
    else {
        std::vector<const variable*> singleParametersVariables = reinterpret_cast<truthFunction*>(m_items[1])->getVariables();
        foundVariables.reserve(singleParametersVariables.size());
        foundVariables.insert(foundVariables.end(), singleParametersVariables.begin(), singleParametersVariables.end());
    }

    return foundVariables;
}

const symbol* truthFunction::operator[](const int p_index) const {
    return m_items[p_index];
}

truthFunction::~truthFunction() {
    delete m_items[0];
    delete m_items[1];
}
