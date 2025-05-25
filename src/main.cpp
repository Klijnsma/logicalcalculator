#include "logicalOperations.hpp"
// #include "operationBlock.hpp"

int main() {
    operationBlock premise1({implication(conjunction('p', 'r'), 'q')});

    return 0;
}
