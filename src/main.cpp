#include "csvParsing.hpp"
#include "truthTable.hpp"

int main() {
    std::unique_ptr<csvParsing::data> formulae = csvParsing::parseFile("test.csv");

    if (!formulae->premises.empty() && formulae->conclusion != nullptr) {
        truthTable wow(formulae->premises, formulae->conclusion);
        wow.print();
    }

    return 0;
}
