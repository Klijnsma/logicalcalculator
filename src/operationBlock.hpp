#pragma once

#include <algorithm>
#include <variant>
#include <vector>

class operationBlock {
public:

    /*
    Constructors for the possible combinations item types:
        - (char, char),
        - (char, operationBlock),
        - (operationBlock, char),
        - (operationBlock, operationBlock)
    */

    operationBlock(char p_item1, char p_item2) {
        // Add variables to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item1) != s_allVariables.end()) {
            s_allVariables.push_back(p_item1);
        }
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item2) != s_allVariables.end()) {
            s_allVariables.push_back(p_item2);
        }

        *variables[0] = p_item1;
        *variables[1] = p_item2;
    }
    operationBlock(char p_item1, operationBlock p_item2) {
        // Add variable to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item1) != s_allVariables.end()) {
            s_allVariables.push_back(p_item1);
        }

        *variables[0] = p_item1;
        *variables[1] = p_item2;
    }
    operationBlock(operationBlock p_item1, char p_item2) {
        // Add variable to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item2) != s_allVariables.end()) {
            s_allVariables.push_back(p_item2);
        }

        *variables[0] = p_item1;
        *variables[1] = p_item2;
    }
    operationBlock(operationBlock p_item1, operationBlock p_item2) {
        *variables[0] = p_item1;
        *variables[1] = p_item2;
    }

    auto operator[](int index) {
        return variables[index];
    }

    std::variant<char, operationBlock>* variables[2];
    inline static std::vector<char> s_allVariables;
};
