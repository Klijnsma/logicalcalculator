#include <array>
#include <fstream>
#include <locale>
#include <memory>
#include <stdexcept>
#include <vector>

#include "csvParsing.hpp"
#include "symbol.hpp"
#include "truthFunction.hpp"
#include "variable.hpp"

namespace csvParsing {

    static std::string lowercaseString(std::string p_input) {
        for (int character = 0; character < p_input.length(); character++) {
            p_input[character] = std::tolower(p_input[character], std::locale());
        }
        return p_input;
    }

    // Declare function beforehand so extractParameters can use it.
    static truthFunction* extractTruthFunction(const std::vector<std::string>& csvBlocks, bool p_positive);

    static std::array<symbol*, 2> extractParameters(std::vector<std::string>& p_parameterBlocks) {
        std::array<symbol*, 2> foundParameters;
        bool positive;

        int parameterCount = 0;
        for (int block = 0; block < p_parameterBlocks.size() && parameterCount < 2; block++) {
            positive = p_parameterBlocks[block][0] != '!';
            if (!positive)
                p_parameterBlocks[block].erase(0, 1);

            if (p_parameterBlocks[block].length() == 1) { // p_parameterBlocks[block] is a variable
                foundParameters[parameterCount] = new variable(p_parameterBlocks[block][0], positive);

                parameterCount++;
            }
            else {
                std::vector<std::string> unparsedBlocks(p_parameterBlocks.size() - block);
                for (int parameterBlock = block; parameterBlock < p_parameterBlocks.size(); parameterBlock++) {
                    unparsedBlocks[parameterBlock - block] = p_parameterBlocks[parameterBlock];
                }
                foundParameters[parameterCount] = extractTruthFunction(unparsedBlocks, positive);

                // Skip the blocks that belong to the truth function just extracted.
                // The truth function keyword's block is dealt with in the for loop statement.
                block += 2 * foundParameters[parameterCount]->getTruthFunctionCount();

                parameterCount++;
            }
        }
        if (parameterCount == 2) {
            return foundParameters;
        }
        throw std::invalid_argument("Could not parse line into truth function parameters.");
    }

    static truthFunction* extractTruthFunction(const std::vector<std::string>& csvBlocks, const bool p_positive) {
        std::vector<std::string> parameterBlocks = csvBlocks;
        parameterBlocks.erase(parameterBlocks.begin());
        const std::array<symbol*, 2> parameters = extractParameters(parameterBlocks);

        // Allow case-insensitive truth function keyword input
        const std::string truthFunctionKeyword = lowercaseString(csvBlocks[0]);

        if (truthFunctionKeyword == "conjunction")
            return new conjunction(parameters[0], parameters[1], p_positive);
        if (truthFunctionKeyword == "exclusive disjunction")
            return new exclusiveDisjunction(parameters[0], parameters[1], p_positive);
        if (truthFunctionKeyword == "inclusive disjunction" || truthFunctionKeyword == "disjunction")
            return new inclusiveDisjunction(parameters[0], parameters[1], p_positive);
        if (truthFunctionKeyword == "material equivalence" || truthFunctionKeyword == "material biconditional" || truthFunctionKeyword == "biconditional")
            return new materialEquivalence(parameters[0], parameters[1], p_positive);
        if (truthFunctionKeyword == "material implication")
            return new materialImplication(parameters[0], parameters[1], p_positive);

        throw std::invalid_argument("Did not recognize truth function type of input longer than one character.");
    }

    static symbol* parseLine(std::ifstream& csvFile) {
        std::string symbolText;
        std::getline(csvFile, symbolText);

        const bool positive = symbolText[0] != '!';

        if (!positive)
            symbolText.erase(0, 1);

        if (symbolText.length() == 1)
            return new variable(symbolText[0], positive);

        if (lowercaseString(symbolText) == "conclusion")
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

        return extractTruthFunction(blocks, positive);
    }

    std::unique_ptr<argumentData> parseFile(const std::string& p_filePath) {
        std::ifstream csv(p_filePath);
        std::unique_ptr<argumentData> parsedData = std::make_unique<argumentData>();

        while (!csv.eof()) {
            parsedData->premises.push_back(parseLine(csv));
            if (parsedData->premises.back() == nullptr) {
                parsedData->conclusion = parseLine(csv);
                parsedData->premises.pop_back();
                break;
            }
        }
        csv.close();

        return parsedData;
    }

}
