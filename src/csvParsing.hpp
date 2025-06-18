#pragma once
#include "symbol.hpp"

namespace csvParsing {

    struct data {
        std::vector<symbol*> premises;
        symbol* conclusion;

        ~data();
    };

    std::unique_ptr<data> parseFile(const std::string& p_filePath);

}
