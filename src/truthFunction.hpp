#pragma once

#include "symbol.hpp"
#include "truthTable.hpp"

class truthFunction : public symbol {
public:
    truthFunction(symbol* p_item1, symbol* p_item2) {
        items.push_back(p_item1);
        items.push_back(p_item2);
    }

    const symbol* operator[](int p_index) const {
        return items[0];
    }

    std::vector<symbol*> items;
    const bool isVariable = false;
};

class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class exclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class inclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class materialEquivalence : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(truthTable* p_truthTable, int row) const override;
    int getTruthFunctionCount() const override;
};
