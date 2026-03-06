#pragma once

#include "symbol.hpp"

class truthTable;

class truthFunction : public symbol {
public:
    truthFunction(symbol* p_item1, symbol* p_item2, bool p_isPositive);

    int getTruthFunctionCount() const override;
    std::string getString() const override;
    std::vector<const variable*> getVariables() const override;

    const symbol* operator[](const int p_index) const;

    ~truthFunction() override;

protected:
    std::vector<symbol*> m_items;
private:
    virtual std::string getOperator() const = 0;
};


class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(const truthTable* p_truthTable, int row) const override;
private:
    std::string getOperator() const override;
};

class exclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(const truthTable* p_truthTable, int row) const override;
private:
    std::string getOperator() const override;
};

class inclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(const truthTable* p_truthTable, int row) const override;
private:
    std::string getOperator() const override;
};

class materialEquivalence : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(const truthTable* p_truthTable, int row) const override;
private:
    std::string getOperator() const override;
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(const truthTable* p_truthTable, int row) const override;
private:
    std::string getOperator() const override;
};
