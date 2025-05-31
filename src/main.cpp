#include "logicalOperations.hpp"
#include "truthTable.hpp"

int main() {
    materialImplication premise1('p', 'q');
    conjunction premise2('p', 'r');
    std::vector<const truthFunction*> premises = {&premise1, &premise2};

    conjunction conclusionTruthFunction({'r', 'q'});
    std::vector<const truthFunction*> conclusion = {&conclusionTruthFunction};

    truthTable wow(premises, {conclusion});

    return 0;
}
