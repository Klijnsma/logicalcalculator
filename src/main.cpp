#include <iostream>

#include "logicalOperations.hpp"

int main() {
    materialEquivalence premise1({'r', 'q'});

    bool a = premise1.calculate(1, 0);

    std::cout << a << '\n';

    return 0;
}
