#pragma once

#include "symbol.hpp"

class truthTable;

class truthFunction : public symbol {
public:
    truthFunction(symbol* p_item1, symbol* p_item2);

    int getTruthFunctionCount() const override;
    std::vector<const variable*> getVariables() const override;

    const symbol* operator[](const int p_index) const;

    ~truthFunction() override;

protected:
    std::vector<symbol*> items;
};

class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
};

class exclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
};

class inclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
};

class materialEquivalence : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() const override;
    bool calculate(const truthTable* p_truthTable, int row) const override;
};
