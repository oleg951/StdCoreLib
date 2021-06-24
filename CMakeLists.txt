cmake_minimum_required(VERSION 3.16)

project(StdCore 
        VERSION 1.2.0
        DESCRIPTION "The core library defines the base componets"
        LANGUAGES CXX)

if (CMAKE_COMPILER_IS_GNUCXX)
message(STATUS "GCC detected, adding compile flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -pipe -Wall -Wextra -pedantic -g3  -std=c++17")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)

enable_testing()

add_subdirectory(test)