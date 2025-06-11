#pragma once
#include "symbol.hpp"

namespace csvParsing {

    class symbolPackage;

    symbolPackage* getSymbol(std::ifstream& csvFile);

}