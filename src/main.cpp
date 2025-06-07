#include <iostream>

#include "logicalOperations.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    variable p('p');
    variable q('q');
    materialImplication premise1(&p, &q);
    variable premise2('q');
    std::vector<const symbol*> premises = {&premise1, &premise2};

    variable conclusion('q');

    truthTable wow(&premises, &conclusion);

    std::cout << premise2.getString() << '\n';

    wow.print();

    return 0;
}
