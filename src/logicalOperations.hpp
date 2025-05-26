#pragma once

#include "truthFunction.hpp"

class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return value1 && value2;
    }
};

class exclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return (value1 || value2) & !(value1 && value2);
    }
};

class inclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return value1 || value2;
    }
};

class materialEquivalence : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return value1 == value2;
    }
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    bool calculate(bool value1, bool value2) {
        return !(!value1 && value2);
    }
};
