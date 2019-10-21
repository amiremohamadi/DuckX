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

configure_file(my_test.docx ${CMAKE_CURRENT_BINARY_DIR}/my_test.docx COPYONLY)
