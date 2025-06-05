#include <iostream>

#include "logicalOperations.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    variable premise1('p');
    conjunction premise2('q', 't');
    conjunction part_premise3('e', 'f');
    materialImplication premise3('v', &part_premise3);
    materialEquivalence part_premise4('t', 'y');
    materialEquivalence premise4('w', &part_premise4);
    materialEquivalence premise5(&part_premise3, &premise4);
    std::vector<const truthFunction*> premises = {&premise3, &premise2, &premise4, &premise5};

    inclusiveDisjunction conclusion('p', 'q');

    truthTable wow(&premises, &conclusion);

    std::cout << premise2.getString() << '\n';

    wow.print();

    return 0;
}
