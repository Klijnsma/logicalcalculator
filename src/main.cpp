#include <fstream>
#include <iostream>

#include "csvParsing.hpp"
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

    std::ifstream test_file;
    test_file.open("test.csv");

    std::cout << csvParsing::getSymbol(test_file) << std::endl;

    test_file.close();

    return 0;
}
