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


    std::map<std::string, std::type_index> truthFunctionTypes = {
        {"conjunction", typeid(conjunction)},
        {"exclusive disjunction", typeid(exclusiveDisjunction)},
        {"inclusive disjunction", typeid(inclusiveDisjunction)},
        {"material equivalence", typeid(materialEquivalence)},
        {"material implication", typeid(materialImplication)},
    };

    symbol* getSymbol(std::ifstream& csvFile) {
        std::string symbolText;
        std::getline(csvFile, symbolText);
        if (symbolText.length() == 1) {
            variable* foundVariable = variable::variableExists(symbolText[0]);
            if (foundVariable != nullptr) {
                return foundVariable;
            }
            return new variable(symbolText[0]);
        }

        // Retrieve blocks as strings.
        std::vector<std::string> blocks;
        int blockIndex = 0;
        int characterOffset = 0;
        int character = 0;
        for (; character < symbolText.length(); character++) {
            if (symbolText[character] == ',') {
                blocks.reserve(blockIndex + 1);
                blocks.push_back(symbolText.substr(characterOffset, character - characterOffset));
                blockIndex++;
                characterOffset = character + 1;
            }
        }
        if (characterOffset < character) {
            blocks.push_back(symbolText.substr(characterOffset, character - characterOffset));
        }

        // Somehow turn blocks string-vector into a truthFunction*.
    }

}
