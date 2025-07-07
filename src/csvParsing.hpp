#pragma once

#include <memory>

#include "argumentData.hpp"

namespace csvParsing {

    std::unique_ptr<argumentData> parseFile(const std::string& p_filePath);

}
