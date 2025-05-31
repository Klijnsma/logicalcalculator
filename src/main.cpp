#include "logicalOperations.hpp"
#include "truthTable.hpp"

int main() {
    materialImplication premise1('p', 'q');
    conjunction premise2('p', 'r');
    std::vector<const truthFunction*> premises = {&premise1, &premise2};

    conjunction conclusion({'r', 'q'});

    truthTable wow(premises, &conclusion);

    return 0;
}
