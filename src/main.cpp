#include <fstream>
#include <iostream>

#include "csvParsing.hpp"
#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    std::ifstream test_file;
    test_file.open("test.csv");
    std::vector<const symbol*> premises;
    symbol* conclusion = nullptr;

    while (!test_file.eof()) {
        premises.push_back(csvParsing::getSymbol(test_file));
        if (premises.back() == nullptr) {
            conclusion = csvParsing::getSymbol(test_file);
            premises.pop_back();
            break;
        }
    }
    test_file.close();

    if (!premises.empty() && conclusion != nullptr) {
        truthTable wow(&premises, conclusion);
        wow.print();
    }

    return 0;
}
