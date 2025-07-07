#include <cstring>
#include <filesystem>
#include <iostream>

#include "csvParsing.hpp"
#include "truthTable.hpp"

int main(const int argv, const char** argc) {
    std::unique_ptr<argumentData> formulae;

    if (argv <= 1)
        return 1;

    for (int argument = 1; argument < argv; argument++) {
        if (strcmp(argc[argument], "-i") == 0 && argument + 1 < argv) {

            if (!std::filesystem::exists(argc[argument + 1]) || !std::filesystem::is_regular_file(argc[argument + 1])) {
                std::cout << "Invalid file \"" << argc[argument + 1] << "\".\n";
                return 1;
            }

            formulae = csvParsing::parseFile(argc[argument + 1]);
            argument++;
        }
        else {
            std::cout << "Invalid argument \"" << argc[argument] << "\".\n";
            return 1;
        }
    }

    if (!formulae->premises.empty() && formulae->conclusion != nullptr) {
        truthTable wow(formulae->premises, formulae->conclusion);
        wow.print();
    }

    return 0;
}
