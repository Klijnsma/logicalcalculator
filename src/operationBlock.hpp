#pragma once

#include <algorithm>
#include <vector>

#define CONJUNCTION 0
#define DISJUNCTION 1
#define NEGATION 2
#define IMPLICATION 3

class operationBlock {
public:
    operationBlock(char p_variable1, int p_operation, char p_variable2) {
        // Add variables to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_variable1) != s_allVariables.end()) {
            s_allVariables.push_back(p_variable1);
        }
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_variable2) != s_allVariables.end()) {
            s_allVariables.push_back(p_variable2);
        }

        variables[0] = p_variable1;
        variables[1] = p_variable2;
        operation = p_operation;
    }

    ~operationBlock() {
        delete[] variables;
    }

    char operator[](int index) {
        return variables[index];
    }

    inline static std::vector<char> s_allVariables;
    char* variables = new char[2];
    int operation;
};
