include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set(SOURCES FastStackBufferTest.cpp)

add_executable(UnitTests ${SOURCES})

target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(UnitTests PRIVATE gtest_main ${PROJECT_NAME})

include(GoogleTest)
gtest_add_tests(TARGET UnitTests)