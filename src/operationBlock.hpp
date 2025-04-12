#pragma once

#include <stdlib.h>

#define CONJUNCTION 0
#define DISJUNCTION 1
#define NEGATION 2
#define IMPLICATION 3

class operationBlock {
    char* variables = new char[2];
public:
    operationBlock(char variable1, int operation_p, char variable2) {
        *variables = variable1;
        *(variables + sizeof(char)) = variable2;

        operation = operation_p;
    }

    ~operationBlock() {
        delete[] variables;
    }

    char operator[](int index) {
        return variables[index];
    }

    int operation;
};
