#include <iostream>

#include "logicalOperations.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    materialImplication premise1('p', 'q');
    inclusiveDisjunction part_premise2('r', 'q');
    conjunction premise2('p', &part_premise2);
    std::vector<const truthFunction*> premises = {&premise1, &premise2};
    variable testVariable('p');

    conjunction conclusion({'r', 'q'});

    truthTable wow(premises, &conclusion);
    std::cout << wow.validity << '\n';
    std::cout << premise2.getString() << '\n';

    std::cout << testVariable.getString() << '\n';

    return 0;
}
