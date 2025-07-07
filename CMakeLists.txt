cmake_minimum_required(VERSION 3.31)

project(logicalcalculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(logicalcalculator src/main.cpp
        src/conjunction.cpp
        src/exclusiveDisjunction.cpp
        src/inclusiveDisjunction.cpp
        src/materialEquivalence.cpp
        src/materialImplication.cpp
        src/csvParsing.cpp
        src/truthFunction.cpp
        src/truthTable.cpp
        src/variable.cpp)
