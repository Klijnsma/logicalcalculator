#pragma once

#include "operationBlock.hpp"

class conjunction : public operationBlock {
public:
    bool calculate(bool value1, bool value2) {
        return value1 && value2;
    }
};

class disjunction : public operationBlock {
public:
    bool calculate(bool value1, bool value2) {
        return value1 || value2;
    }
};

class implication : public operationBlock {
public:
    bool calculate(bool value1, bool value2) {
        return !(!value1 && value2);
    }
};
