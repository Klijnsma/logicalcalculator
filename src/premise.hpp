#pragma once

#include <vector>

#include "operationBlock.hpp"

class premise {
public:
    premise(std::vector<operationBlock> operations_p) {
        operations = operations_p;
    }

    std::vector<operationBlock> operations;
};
