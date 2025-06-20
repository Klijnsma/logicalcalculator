#pragma once

#include <vector>

#include "symbol.hpp"

struct argumentData {
    std::vector<symbol*> premises;
    symbol* conclusion;

    ~argumentData() {
        for (int premise = 0; premise < premises.size(); premise++) {
            delete premises[premise];
        }
        delete conclusion;
    }
};
