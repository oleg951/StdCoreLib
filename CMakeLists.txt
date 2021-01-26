cmake_minimum_required(VERSION 3.0)

project(StdCore 
        VERSION 0.1.0
        DESCRIPTION "The core library defines the base componets"
        LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -pipe -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc -g3  -std=c++17")

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.h)

set(BIN_PATH ${PROJECT_SOURCE_DIR}/bin)

set(HEADERS_PATH "$ENV{CINCLUDE}/stdCore")
set(DESTINATION_PATH "$ENV{CLIBS}")

message("BUILDING ${PROJECT_NAME}...")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_definitions(-DSOME_IMPORTANT_DEFINITION)

install(TARGETS ${PROJECT_NAME} 
        DESTINATION ${DESTINATION_PATH})
install(TARGETS ${PROJECT_NAME} 
        DESTINATION ${BIN_PATH})
install (FILES ${HEADERS} 
       DESTINATION ${HEADERS_PATH})