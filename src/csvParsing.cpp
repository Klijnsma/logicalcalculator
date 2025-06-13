#include <array>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "csvParsing.hpp"
#include "symbol.hpp"
#include "truthFunction.hpp"
#include "variable.hpp"

namespace csvParsing {
    std::array<symbol*, 2> extractParameters(const std::vector<std::string>& p_parameterBlocks) {
        std::array<symbol*, 2> foundParameters;
        int parameterCount = 0;

        for (int block = 0; block < p_parameterBlocks.size() && parameterCount < 2; block++) {
            if (p_parameterBlocks[block].length() == 1) { // p_parameterBlocks[block] is a variable
                variable* existentVariable = variable::variableExists(p_parameterBlocks[block][0]);
                if (existentVariable == nullptr)
                    foundParameters[parameterCount] = new variable(p_parameterBlocks[block][0]);
                else
                    foundParameters[parameterCount] = existentVariable;

                parameterCount++;
            }
            else {
                std::vector<std::string> nextParameterBlocks = p_parameterBlocks;
                nextParameterBlocks.erase(nextParameterBlocks.begin());
                const std::array<symbol*, 2> parameters = extractParameters(nextParameterBlocks);

                if (p_parameterBlocks[block] == "conjunction")
                    foundParameters[parameterCount] = new conjunction(parameters[0], parameters[1]);
                if (p_parameterBlocks[block] == "exclusive disjunction")
                    foundParameters[parameterCount] = new exclusiveDisjunction(parameters[0], parameters[1]);
                if (p_parameterBlocks[block] == "inclusive disjunction")
                    foundParameters[parameterCount] = new inclusiveDisjunction(parameters[0], parameters[1]);
                if (p_parameterBlocks[block] == "material equivalence")
                    foundParameters[parameterCount] = new materialEquivalence(parameters[0], parameters[1]);
                if (p_parameterBlocks[block] == "material implication")
                    foundParameters[parameterCount] = new materialImplication(parameters[0], parameters[1]);
                else
                    throw std::invalid_argument("Did not recognize truth function type of input longer than one character.");

                // Skip the blocks that belong to the truth function just extracted.
                // The truth function's block is dealt with in the for loop statement.
                block += 2 * foundParameters[parameterCount]->getTruthFunctionCount();

                parameterCount++;
            }
        }
        if (parameterCount == 2) {
            return foundParameters;
        }
        throw std::invalid_argument("Could not parse line into truth function parameters.");
    }

    truthFunction* extractTruthFunction(const std::vector<std::string>& csvBlocks) {
        if (csvBlocks[0].length() > 1) {
            std::vector<std::string> parameterBlocks = csvBlocks;
            parameterBlocks.erase(parameterBlocks.begin());
            const std::array<symbol*, 2> parameters = extractParameters(parameterBlocks);

            if (csvBlocks[0] == "conjunction")
                return new conjunction(parameters[0], parameters[1]);
            if (csvBlocks[0] == "exclusive disjunction")
                return new exclusiveDisjunction(parameters[0], parameters[1]);
            if (csvBlocks[0] == "inclusive disjunction")
                return new inclusiveDisjunction(parameters[0], parameters[1]);
            if (csvBlocks[0] == "material equivalence")
                return new materialEquivalence(parameters[0], parameters[1]);
            if (csvBlocks[0] == "material implication")
                return new materialImplication(parameters[0], parameters[1]);

            throw std::invalid_argument("Did not recognize truth function type of input longer than one character.");
        }
        throw std::invalid_argument("Lines must either contain a solitary variable or start with a truth function name");
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
