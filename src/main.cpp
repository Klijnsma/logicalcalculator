#include <iostream>

#include "logicalOperations.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    materialImplication premise1('p', 'q');
    exclusiveDisjunction part_premise2('r', 'q');
    conjunction premise2('p', &part_premise2);
    std::vector<const truthFunction*> premises = {&premise1, &premise2};
    variable testVariable('p');

    conjunction conclusion({'r', 'q'});

    truthTable wow(&premises, &conclusion);

    std::cout << premise2.getString() << '\n';

    std::cout << testVariable.getString() << '\n';

    wow.print();

    return 0;
}
