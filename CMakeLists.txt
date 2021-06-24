cmake_minimum_required(VERSION 3.0)

project(StdCore 
        VERSION 1.2.0
        DESCRIPTION "The core library defines the base componets"
        LANGUAGES CXX)

if (CMAKE_COMPILER_IS_GNUCXX)
message(STATUS "GCC detected, adding compile flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -pipe -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc -g3  -std=c++17")
endif(CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory("src")
