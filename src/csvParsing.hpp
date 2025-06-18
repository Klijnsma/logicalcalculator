#pragma once

#include "argumentData.hpp"
#include "symbol.hpp"

namespace csvParsing {

    std::unique_ptr<argumentData> parseFile(const std::string& p_filePath);

}
