#pragma once

#include "symbol.hpp"

class truthTable;
class symbol;

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
