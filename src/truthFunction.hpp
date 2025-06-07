#pragma once

#include <algorithm>
#include <string>
#include <variant>
#include <vector>

class truthTable;

class calculation {
public:
    virtual bool calculate(truthTable* p_truthTable, int row) const = 0;
    virtual std::string getString() const = 0;
    virtual int getTruthFunctionCount() const = 0;
};

class truthFunction : public calculation {
public:

    /*
    Constructors for the possible combinations item types:
        - (char, char),
        - (char, truthFunction),
        - (truthFunction, char),
        - (truthFunction, truthFunction)
    */

    truthFunction() = default;

    truthFunction(char p_item1, char p_item2) {
        // Add variables to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item1) == s_allVariables.end())
            s_allVariables.push_back(p_item1);

        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item2) == s_allVariables.end())
            s_allVariables.push_back(p_item2);

        items.push_back(p_item1);
        items.push_back(p_item2);
    }
    truthFunction(char p_item1, truthFunction* p_item2) {
        // Add variable to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item1) == s_allVariables.end())
            s_allVariables.push_back(p_item1);

        items.push_back(p_item1);
        items.push_back(p_item2);
    }
    truthFunction(truthFunction* p_item1, char p_item2) {
        // Add variable to s_allVariables if not in there yet.
        if (std::find(s_allVariables.begin(), s_allVariables.end(), p_item2) == s_allVariables.end())
            s_allVariables.push_back(p_item2);

        items.push_back(p_item1);
        items.push_back(p_item2);
    }
    truthFunction(truthFunction* p_item1, truthFunction* p_item2) {
        items.push_back(p_item1);
        items.push_back(p_item2);
    }

    const auto operator[](int p_index) {
        return std::get<0>(items[p_index]);
    }

    std::vector<std::variant<char, truthFunction*>> items;
    inline static std::vector<char> s_allVariables;
};
