#include <iostream>

#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    variable p('p');
    variable q('q');
    materialImplication premise1(&p, &q);
    std::vector<const symbol*> premises = {&premise1, &p};

    truthTable wow(&premises, &q);

    wow.print();

    return 0;
}
