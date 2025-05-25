#pragma once

#include "truthFunction.hpp"

class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return value1 && value2;
    }
};

class disjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return value1 || value2;
    }
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return !(!value1 && value2);
    }
};
