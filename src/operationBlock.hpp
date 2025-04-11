#pragma once

#include <stdlib.h>

#define CONJUNCTION 0
#define DISJUNCTION 1
#define NEGATION 2
#define IMPLICATION 3

class operationBlock {
    void* variables = malloc(sizeof(char) * 2);
public:
    operationBlock(char variable1, int operation_p, char variable2) {
        *(char*)variables = variable1;
        *((char*)variables + sizeof(char)) = variable2;

        operation = operation_p;
    }

    ~operationBlock() {
        free(variables);
    }

    char operator[](int index) {
        return ((char*)variables)[index];
    }

    int operation;
};
