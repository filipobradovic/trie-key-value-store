cmake_minimum_required(VERSION 3.26.4)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

add_executable("${PROJECT_NAME}Test"
    SimpleTrieTest.cpp
    TrieTest.cpp
)

target_link_libraries(
    "${PROJECT_NAME}Test"
    GTest::gtest_main
    TrieKeyValueStoreLib
)

include(GoogleTest)
gtest_discover_tests("${PROJECT_NAME}Test")
