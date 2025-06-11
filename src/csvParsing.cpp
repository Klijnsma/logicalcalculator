#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <typeindex>
#include <algorithm>

#include "csvParsing.hpp"
#include "symbol.hpp"
#include "truthFunction.hpp"
#include "variable.hpp"

namespace csvParsing {

    class symbolPackage {
    public:
        symbolPackage(truthFunction* p_mainSymbol, symbol* parameter1, symbol* parameter2) {
            mainSymbol = p_mainSymbol;
            parameters.push_back(parameter1);
            parameters.push_back(parameter2);
        }

        symbolPackage(char p_mainSymbol) {
            mainSymbol = new variable(p_mainSymbol);
        }

        symbol* mainSymbol;
        std::vector<symbol*> parameters;
    };

    std::map<std::string, std::type_index> truthFunctionTypes = {
        {"conjunction", typeid(conjunction)},
        {"exclusive disjunction", typeid(exclusiveDisjunction)},
        {"inclusive disjunction", typeid(inclusiveDisjunction)},
        {"material equivalence", typeid(materialEquivalence)},
        {"material implication", typeid(materialImplication)},
    };

    symbolPackage* getSymbol(std::ifstream& csvFile) {
        char symbolTextBuffer;
        csvFile >> symbolTextBuffer;
        std::string symbolText;

        while (symbolTextBuffer != ',') {
            symbolText += symbolTextBuffer;
            csvFile >> symbolTextBuffer;
        }

        if (symbolText.length() == 1) {
            return new symbolPackage(static_cast<char>(symbolText[0]));
        }
    }

}
