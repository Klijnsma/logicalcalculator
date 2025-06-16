#pragma once

#include <vector>
#include <string>

#include "symbol.hpp"

class truthTable;

class truthFunction : public symbol {
public:
    truthFunction(symbol* p_item1, symbol* p_item2) {
        items.push_back(p_item1);
        items.push_back(p_item2);

        isVariable = false;
    }

    const symbol* operator[](const int p_index) const {
        return items[p_index];
    }

    std::vector<const variable*> getVariables() const override {
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

protected:
    std::vector<symbol*> items;
};

class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class exclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class inclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class materialEquivalence : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};
