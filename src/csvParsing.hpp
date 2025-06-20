#pragma once

#include "argumentData.hpp"

namespace csvParsing {

    std::unique_ptr<argumentData> parseFile(const std::string& p_filePath);

}
