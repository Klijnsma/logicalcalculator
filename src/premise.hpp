#pragma once

#include <algorithm>
#include <vector>

#include "operationBlock.hpp"

class premise {
    static std::vector<char> variables;
public:
    premise(std::vector<operationBlock> operations_p) {
        for (int i = 0; i < operations_p.size(); i++) {
            if (std::find(variables.begin(), variables.end(), operations_p[i][0]) != variables.end()) {
                variables.push_back(operations_p[i][0]);
            }

            if (std::find(variables.begin(), variables.end(), operations_p[i][1]) != variables.end()) {
                variables.push_back(operations_p[i][1]);
            }

            operations = operations_p;
        }
    }

    std::vector<operationBlock> operations;
};
