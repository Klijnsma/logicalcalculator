#include <array>
#include <fstream>
#include <memory>
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

        truthFunction* extractTruthFunction(const std::vector<std::string>& csvBlocks);

        for (int block = 0; block < p_parameterBlocks.size() && parameterCount < 2; block++) {
            if (p_parameterBlocks[block].length() == 1) { // p_parameterBlocks[block] is a variable
                foundParameters[parameterCount] = new variable(p_parameterBlocks[block][0]);

                parameterCount++;
            }
            else {
                foundParameters[parameterCount] = extractTruthFunction(p_parameterBlocks);

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

    symbol* parseLine(std::ifstream& csvFile) {
        std::string symbolText;
        std::getline(csvFile, symbolText);
        if (symbolText.length() == 1)
            return new variable(symbolText[0]);

        if (symbolText == "conclusion")
            return nullptr;

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

    std::unique_ptr<argumentData> parseFile(const std::string& p_filePath) {
        std::ifstream csv(p_filePath);
        std::unique_ptr<argumentData> parsedData = std::make_unique<argumentData>();

        while (!csv.eof()) {
            parsedData->premises.push_back(csvParsing::parseLine(csv));
            if (parsedData->premises.back() == nullptr) {
                parsedData->conclusion = csvParsing::parseLine(csv);
                parsedData->premises.pop_back();
                break;
            }
        }
        csv.close();

        return parsedData;
    }

}
