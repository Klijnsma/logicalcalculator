#pragma once

#include <cmath>
#include <stdexcept>

#include "truthFunction.hpp"

class truthTable {
public:
    truthTable(const std::vector<const truthFunction*>& premises, const truthFunction* conclusion) {
        variableCount = truthFunction::s_allVariables.size();
        columns = variableCount + premises.size();
        rows = std::pow(2, variableCount);

        variableCombinations = new bool*[variableCount];

        // Calculate every possible truth value combination for the given amount of variables and store them in possibleTruthValues.
        for (int variable = 0; variable < variableCount; variable++) {
            variableCombinations[variable] = new bool[rows];
            int blockSize = rows / std::pow(2, variable + 1);
            bool truthValue = true;

            for (int block = 0; block < rows / blockSize; block++) {
                // Alternate the boolean value for the variable being worked on.
                std::fill(&variableCombinations[variable][block * blockSize],
                          &variableCombinations[variable][block * blockSize + blockSize], truthValue);
                truthValue = !truthValue;
            }
        }

        premiseResults = new bool*[premises.size()];

        // Calculate the results of the premises in each row.
        for (int currentPremise = 0; currentPremise < premises.size(); currentPremise++) {
            premiseResults[currentPremise] = new bool[rows];

            for (int currentRow = 0; currentRow < rows; currentRow++) {
                // Dealing with truthFunctions inside truthFunctions is dealt with by the calculate() function.
                premiseResults[currentPremise][currentRow] = premises[currentPremise]->calculate(this, currentRow);
            }
        }

        combinedPremiseResults = new bool[rows];
        conclusionTruth = new bool[rows];
        conclusionFollowsFromPremises = new bool[rows];

        int followingConclusions = 0;

        // Calculate for each row whether all premises are true, whether the conclusion is true
        // and whether the conclusion is materially implied by the premises.
        for (int currentRow = 0; currentRow < rows; currentRow++) {
            int currentPremise = 0;

            for (; currentPremise < premises.size(); currentPremise++) {
                if (!premiseResults[currentPremise][currentRow]) {
                    combinedPremiseResults[currentRow] = false;
                    break;
                }
            }
            if (currentPremise == premises.size())
                combinedPremiseResults[currentRow] = true;

            conclusionTruth[currentRow] = conclusion->calculate(this, currentRow);
            conclusionFollowsFromPremises[currentRow] = !(combinedPremiseResults[currentRow] && !conclusionTruth[currentRow]);
            if (conclusionFollowsFromPremises[currentRow])
                followingConclusions++;
        }

        if (followingConclusions == rows) {
            validity = true;
            return;
        }
        validity = false;
    }

    bool getTruthValue(char variable, int row) {
        int variableNumber = std::distance(truthFunction::s_allVariables.begin(),
                                           std::find(truthFunction::s_allVariables.begin(), truthFunction::s_allVariables.end(), variable));

        if (std::find(truthFunction::s_allVariables.begin(), truthFunction::s_allVariables.end(), variable)
            != truthFunction::s_allVariables.end()) {

            return variableCombinations[variableNumber][row];
        }

        throw std::invalid_argument("[truthTable::getTruthValue()]: Variable not found in truthFunction::s_allVariables");
    }

    ~truthTable() {
        for (int variable = 0; variable < variableCount; variable++) {
            delete[] variableCombinations[variable];
        }
        delete[] variableCombinations;

        for (int premise = 0; premise < columns - variableCount; premise++) {
            delete[] premiseResults[premise];
        }
        delete[] premiseResults;

        delete[] combinedPremiseResults;
        delete[] conclusionTruth;
        delete[] conclusionFollowsFromPremises;
    }

    int columns;
    int rows;
    int variableCount;

    // Storage for the actual truth table.
    bool** variableCombinations;
    bool** premiseResults;
    bool* combinedPremiseResults;
    bool* conclusionTruth;
    bool* conclusionFollowsFromPremises;

    bool validity;
};
