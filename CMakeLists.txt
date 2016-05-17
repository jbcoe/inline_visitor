cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)

include_directories(SYSTEM external/catch/include)
include_directories(include)

add_subdirectory(tests)

enable_testing()

add_test(test_inline_visitor ${CMAKE_BINARY_DIR}/tests/test_inline_visitor -s)
