cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)

# Install doctest
if(NOT EXISTS ${CMAKE_BINARY_DIR}/doctest.h)
    file(DOWNLOAD
        https://github.com/doctest/doctest/releases/download/v2.4.9/doctest.h
        doctest.h)
endif()
include_directories(${CMAKE_BINARY_DIR})

configure_file(sample.docx ${CMAKE_BINARY_DIR}/sample.docx COPYONLY)

# Tests
add_executable(basic_tests basic_tests.cpp)
target_link_libraries(basic_tests duckx)
add_test(NAME basic_tests COMMAND basic_tests)

add_executable(iterator_tests iterator_tests.cpp)
target_link_libraries(iterator_tests duckx)
add_test(NAME iterator_tests COMMAND iterator_tests)

