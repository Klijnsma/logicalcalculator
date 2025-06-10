#include <fstream>
#include <iostream>
#include <vector>

#include "csvParsing.hpp"
#include "symbol.hpp"
#include "truthFunction.hpp"
#include "variable.hpp"

namespace csvParsing {

    symbol* getSymbol(std::ifstream& csvFile) {
        char symbolTextBuffer;
        std::string symbolText;

        while (symbolTextBuffer != ',') {
            symbolText += symbolTextBuffer;
            csvFile >> symbolTextBuffer;
        }
        if (symbolText.length() == 1) {
            return new variable(static_cast<char>(symbolText[0]));
        }
    }

}
