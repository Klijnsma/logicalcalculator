#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "csvParsing.hpp"
#include "symbol.hpp"
#include "truthFunction.hpp"
#include "variable.hpp"

namespace csvParsing {

    std::array<std::string, 5> truthFunctionTypes = {
        "conjunction",
        "exclusive disjunction",
        "inclusive disjunction",
        "material equivalence",
        "material implication",
    };

    std::array<symbol*, 2> extractParameters(std::vector<std::string> p_parameterBlocks) {}

    truthFunction* extractTruthFunction(std::vector<std::string> csvBlocks) {
        int foundVariables = 0;
        int variableIndices[2];

        for (int block = 0; block < csvBlocks.size() && foundVariables < 2; block++) {
            if (csvBlocks[block].length() > 1) {
                if (std::find(truthFunctionTypes.begin(),truthFunctionTypes.end(), csvBlocks[block])) {
                    std::vector<std::string> parameterBlocks;
                    parameterBlocks.assign(csvBlocks.begin(), csvBlocks.end());
                    const std::array<symbol*, 2> parameters = extractParameters(parameterBlocks);
                    if (csvBlocks[block] == "conjunction") {
                        return new conjunction(parameters[0], parameters[1]);
                    }
                    if (csvBlocks[block] == "exclusive disjunction") {
                        return new exclusiveDisjunction(parameters[0], parameters[1]);
                    }
                    if (csvBlocks[block] == "inclusive disjunction") {
                        return new inclusiveDisjunction(parameters[0], parameters[1]);
                    }
                    if (csvBlocks[block] == "material equivalence") {
                        return new materialEquivalence(parameters[0], parameters[1]);
                    }
                    if (csvBlocks[block] == "material implication") {
                        return new materialImplication(parameters[0], parameters[1]);
                    }
                }
                else {
                    throw std::invalid_argument("Did not recognize truth function type of input longer than one character.");
                }
            }
            else if (block == 0) {
                throw std::invalid_argument("Lines must either contain a solitary variable or start with a truth function name");
            }
        }
    }

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

        return extractTruthFunction(blocks);
    }

}
