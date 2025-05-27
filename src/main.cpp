#include <iostream>

#include "logicalOperations.hpp"

int main() {
    materialEquivalence premise1({'r', 'q'});

    bool a = premise1.calculate(true, true);

    std::cout << a << '\n';

    return 0;
}
