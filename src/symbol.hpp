#pragma once

#include <string>
#include <vector>

class truthTable;
class variable;

class symbol {
public:
    virtual bool calculate(const truthTable* p_truthTable, int row) const = 0;
    virtual std::string getString() const = 0;
    virtual int getTruthFunctionCount() const = 0;
    virtual std::vector<const variable*> getVariables() const = 0;

    virtual ~symbol() = default;

    bool isVariable;

protected:
    inline static std::vector<char> s_allVariables;
};
