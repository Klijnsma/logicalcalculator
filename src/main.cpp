#include <iostream>

#include <algorithm>

#include "logicalOperations.hpp"
#include "truthTable.hpp"

int main() {
    conjunction premise1({conjunction{'a', 't'}, 'e'});
    conjunction premise2({'p', 'q'});

    inclusiveDisjunction conclusion({'p', 't'});

    truthTable wow({{premise1}, {premise2}}, {conclusion});

    std::cout << '\n';

    // Prints a table of variable all possible variable combinations with four variables.
    for (int i = 0; i < wow.rows; i++) {
        std::cout << wow.variableCombinations[0][i] << ' ';
        std::cout << wow.variableCombinations[1][i] << ' ';
        std::cout << wow.variableCombinations[2][i] << ' ';
        std::cout << wow.variableCombinations[3][i] << ' ';
        std::cout << wow.variableCombinations[4][i] << '\n';
    }

    return 0;
}
