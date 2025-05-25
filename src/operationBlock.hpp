#pragma once

#include <algorithm>
#include <variant>
#include <vector>

class operationBlock {
public:

    /*
    Constructors for the possible combinations item type:
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

        items.push_back(p_item1);
        items.push_back(p_item2);
    }
    operationBlock(char p_item1, operationBlock p_item2) {
        // Add variable to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item1) != s_allVariables.end()) {
            s_allVariables.push_back(p_item1);
        }

        items.push_back(p_item1);
        items.push_back(p_item2);
    }
    operationBlock(operationBlock p_item1, char p_item2) {
        // Add variable to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item2) != s_allVariables.end()) {
            s_allVariables.push_back(p_item2);
        }

        items.push_back(p_item1);
        items.push_back(p_item2);
    }
    operationBlock(operationBlock p_item1, operationBlock p_item2) {
        items.push_back(p_item1);
        items.push_back(p_item2);
    }

    auto operator[](int p_index) {
        return items[p_index];
    }

    std::vector<std::variant<char, operationBlock>> items;
    inline static std::vector<char> s_allVariables;
};
