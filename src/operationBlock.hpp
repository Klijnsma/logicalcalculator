#pragma once

#include <algorithm>
#include <vector>

class operationBlock {
public:
    operationBlock(char p_variable1, char p_variable2) {
        // Add variables to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_variable1) != s_allVariables.end()) {
            s_allVariables.push_back(p_variable1);
        }
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_variable2) != s_allVariables.end()) {
            s_allVariables.push_back(p_variable2);
        }

        variables[0] = p_variable1;
        variables[1] = p_variable2;
    }

    ~operationBlock() {
        delete[] variables;
    }

    char operator[](int index) {
        return variables[index];
    }

    char* variables = new char[2];
protected:
    inline static std::vector<char> s_allVariables;
};
