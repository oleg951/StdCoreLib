cmake_minimum_required(VERSION 3.0)

project(StdCore 
        VERSION 1.0.0
        DESCRIPTION "The core library defines the base componets"
        LANGUAGES CXX)

if (CMAKE_COMPILER_IS_GNUCXX)
message(STATUS "GCC detected, adding compile flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -pipe -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc -g3  -std=c++2a")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(SOURCES "${PROJECT_SOURCE_DIR}/src/UserException.cpp" "${PROJECT_SOURCE_DIR}/src/LogHelper.cpp")

set(HEADERS "${PROJECT_SOURCE_DIR}/src/CharFastStackBuffer.h"
"${PROJECT_SOURCE_DIR}/src/FastStackStreamBuffer.h" 
"${PROJECT_SOURCE_DIR}/src/LogHelper.h" 
"${PROJECT_SOURCE_DIR}/src/UserException.h"
"${PROJECT_SOURCE_DIR}/src/FastStackBuffer.h")

set(BIN_PATH ${PROJECT_SOURCE_DIR}/bin)

set(HEADERS_PATH "$ENV{CINCLUDE}/stdCore")
set(DESTINATION_PATH "$ENV{CLIBS}")

file(REMOVE_RECURSE "${PROJECT_SOURCE_DIR}/bin")

message("BUILDING ${PROJECT_NAME}...")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

add_definitions(-DSOME_IMPORTANT_DEFINITION)

install(TARGETS ${PROJECT_NAME} 
        DESTINATION ${DESTINATION_PATH})
install(TARGETS ${PROJECT_NAME} 
        DESTINATION ${BIN_PATH})
install (FILES ${HEADERS} 
       DESTINATION ${HEADERS_PATH})
