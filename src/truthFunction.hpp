#pragma once

#include <string>
#include <vector>

class truthTable;
class variable;

class symbol {
public:
    virtual bool calculate(truthTable* p_truthTable, int row) const = 0;
    virtual std::string getString() const = 0;
    virtual int getTruthFunctionCount() const = 0;

    inline static std::vector<variable*> s_allVariables;
    bool isVariable;
};

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
