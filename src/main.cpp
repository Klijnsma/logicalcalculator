#include <fstream>
#include <iostream>

#include "csvParsing.hpp"
#include "truthFunction.hpp"
#include "truthTable.hpp"
#include "variable.hpp"

int main() {
    std::unique_ptr<csvParsing::data> formulae = csvParsing::parseFile("test.csv");

    if (!formulae->premises.empty() && formulae->conclusion != nullptr) {
        truthTable wow(formulae->premises, formulae->conclusion);
        wow.print();
    }

    return 0;
}
