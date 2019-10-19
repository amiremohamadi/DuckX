add_executable(
        unit_tests
        basic_tests.cpp
)

target_link_libraries(
        unit_tests
        gtest_main
        duckx
)

add_test(
        NAME
        unit
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)

configure_file(my_test.docx ${CMAKE_CURRENT_BINARY_DIR}/my_test.docx COPYONLY)