#include <fstream>
#include <iostream>
#include <map>
#include <typeindex>
#include <vector>

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

        symbolPackage(variable* p_mainSymbol) {
            mainSymbol = p_mainSymbol;
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
        std::string symbolText;
        std::getline(csvFile, symbolText);
        if (symbolText.length() == 1) {
            variable* foundVariable = variable::variableExists(symbolText[0]);
            if (foundVariable != nullptr) {
                return new symbolPackage(foundVariable);
            }
            return new symbolPackage(static_cast<char>(symbolText[0]));
        }

        symbolPackage* packagedSymbol;

        std::vector<std::string> blocks;
        int blockIndex = 0;
        int characterOffset = 0;
        int character = 0;
        for (; character < symbolText.length(); character++) {
            if (symbolText[character] == ',') {
                // Retrieve blocks as strings.
                blocks.reserve(blockIndex + 1);
                blocks.push_back(symbolText.substr(characterOffset, character - characterOffset));
                blockIndex++;
                characterOffset = character + 1;
            }
        }
        if (characterOffset < character) {
            blocks.push_back(symbolText.substr(characterOffset, character - characterOffset));
        }
    }

}
