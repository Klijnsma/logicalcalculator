#include "premise.hpp"

int main() {
    premise premise1({operationBlock('p', operationBlock('q', 'p'))});

    return 0;
}
