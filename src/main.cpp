#include <iostream>

#include "logicalOperations.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    materialImplication premise1('p', 'q');
    exclusiveDisjunction premise2('q', 'd');
    variable premise3('r');
    variable premise4('a');
    conjunction premise5('a', 'f');
    std::vector<const truthFunction*> premises = {&premise1, &premise2, &premise3, &premise4, &premise5};

    variable conclusion('p');

    truthTable wow(&premises, &conclusion);

    std::cout << premise2.getString() << '\n';

    wow.print();

    return 0;
}
