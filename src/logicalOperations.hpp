#pragma once

#include "truthFunction.hpp"
#include "truthTable.hpp"

class conjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() override {
        std::string premiseString;

        if (std::holds_alternative<char>(items[0]))
            premiseString = std::get<char>(items[0]);
        else
            premiseString = '(' + std::get<truthFunction*>(items[0])->getString() + ')';

        premiseString += " ∧ ";

        if (std::holds_alternative<char>(items[1]))
            premiseString += std::get<char>(items[1]);
        else
            premiseString += '(' + std::get<truthFunction*>(items[1])->getString() + ')';

        return premiseString;
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        bool value1, value2;

        if (std::holds_alternative<char>(items[0]))
            // Get the truth value for the char variables in the given row.
            value1 = p_truthTable->getTruthValue(std::get<char>(items[0]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value1 = std::get<truthFunction*>(items[0])->calculate(p_truthTable, row);

        if (std::holds_alternative<char>(items[1]))
            // Get the truth value for the char variables in the given row.
            value2 = p_truthTable->getTruthValue(std::get<char>(items[1]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value2 = std::get<truthFunction*>(items[1])->calculate(p_truthTable, row);

        return value1 && value2;
    }
};

class exclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() override {
        std::string premiseString;

        if (std::holds_alternative<char>(items[0]))
            premiseString = std::get<char>(items[0]);
        else
            premiseString = '(' + std::get<truthFunction*>(items[0])->getString() + ')';

        premiseString += " ⊻ ";

        if (std::holds_alternative<char>(items[1]))
            premiseString += std::get<char>(items[1]);
        else
            premiseString += '(' + std::get<truthFunction*>(items[1])->getString() + ')';

        return premiseString;
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        bool value1, value2;

        if (std::holds_alternative<char>(items[0]))
            // Get the truth value for the char variables in the given row.
            value1 = p_truthTable->getTruthValue(std::get<char>(items[0]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value1 = std::get<truthFunction*>(items[0])->calculate(p_truthTable, row);

        if (std::holds_alternative<char>(items[1]))
            // Get the truth value for the char variables in the given row.
            value2 = p_truthTable->getTruthValue(std::get<char>(items[1]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value2 = std::get<truthFunction*>(items[1])->calculate(p_truthTable, row);

        return (value1 || value2) && !(value1 && value2);
    }
};

class inclusiveDisjunction : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() override {
        std::string premiseString;

        if (std::holds_alternative<char>(items[0]))
            premiseString = std::get<char>(items[0]);
        else
            premiseString = '(' + std::get<truthFunction*>(items[0])->getString() + ')';

        premiseString += " ∨ ";

        if (std::holds_alternative<char>(items[1]))
            premiseString += std::get<char>(items[1]);
        else
            premiseString += '(' + std::get<truthFunction*>(items[1])->getString() + ')';

        return premiseString;
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        bool value1, value2;

        if (std::holds_alternative<char>(items[0]))
            // Get the truth value for the char variables in the given row.
            value1 = p_truthTable->getTruthValue(std::get<char>(items[0]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value1 = std::get<truthFunction*>(items[0])->calculate(p_truthTable, row);

        if (std::holds_alternative<char>(items[1]))
            // Get the truth value for the char variables in the given row.
            value2 = p_truthTable->getTruthValue(std::get<char>(items[1]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value2 = std::get<truthFunction*>(items[1])->calculate(p_truthTable, row);

        return value1 || value2;
    }
};

class materialEquivalence : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() override {
        std::string premiseString;

        if (std::holds_alternative<char>(items[0]))
            premiseString = std::get<char>(items[0]);
        else
            premiseString = '(' + std::get<truthFunction*>(items[0])->getString() + ')';

        premiseString += " ↔ ";

        if (std::holds_alternative<char>(items[1]))
            premiseString += std::get<char>(items[1]);
        else
            premiseString += '(' + std::get<truthFunction*>(items[1])->getString() + ')';

        return premiseString;
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        bool value1, value2;

        if (std::holds_alternative<char>(items[0]))
            // Get the truth value for the char variables in the given row.
            value1 = p_truthTable->getTruthValue(std::get<char>(items[0]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value1 = std::get<truthFunction*>(items[0])->calculate(p_truthTable, row);

        if (std::holds_alternative<char>(items[1]))
            // Get the truth value for the char variables in the given row.
            value2 = p_truthTable->getTruthValue(std::get<char>(items[1]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value2 = std::get<truthFunction*>(items[1])->calculate(p_truthTable, row);

        return value1 == value2;
    }
};

class materialImplication : public truthFunction {
public:
    using truthFunction::truthFunction;

    std::string getString() override {
        std::string premiseString;

        if (std::holds_alternative<char>(items[0]))
            premiseString = std::get<char>(items[0]);
        else
            premiseString = '(' + std::get<truthFunction*>(items[0])->getString() + ')';

        premiseString += " → ";

        if (std::holds_alternative<char>(items[1]))
            premiseString += std::get<char>(items[1]);
        else
            premiseString += '(' + std::get<truthFunction*>(items[1])->getString() + ')';

        return premiseString;
    }

    bool calculate(truthTable* p_truthTable, int row) const override {
        bool value1, value2;

        if (std::holds_alternative<char>(items[0]))
            // Get the truth value for the char variables in the given row.
            value1 = p_truthTable->getTruthValue(std::get<char>(items[0]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value1 = std::get<truthFunction*>(items[0])->calculate(p_truthTable, row);

        if (std::holds_alternative<char>(items[1]))
            // Get the truth value for the char variables in the given row.
            value2 = p_truthTable->getTruthValue(std::get<char>(items[1]), row);
        else
            // Make sure any nested truthFunctions are calculated first.
            value2 = std::get<truthFunction*>(items[1])->calculate(p_truthTable, row);

        return !(value1 && !value2);
    }
};
