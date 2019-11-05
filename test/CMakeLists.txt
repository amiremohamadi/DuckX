set (CMAKE_CXX_STANDARD 11)

add_executable(
    unit_tests
    basic_tests.cpp
)

target_link_libraries(
    unit_tests
    duckx
)

add_test(
    NAME
    unit
    COMMAND
    unit_tests
)

add_executable(
    iterator_tests
    iterator_tests.cpp
)

target_link_libraries(
    iterator_tests
    duckx
)

add_test(
    NAME
    iterator
    COMMAND
    iterator_tests
)

# Need C++11 for iterator tests
set_target_properties(iterator_tests PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

configure_file(my_test.docx ${CMAKE_CURRENT_BINARY_DIR}/my_test.docx COPYONLY)
