cmake_minimum_required(VERSION 3.0)

project(duckx VERSION 0.2)

set(CMAKE_CXX_STANDARD 11)

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)

set(HEADERS src/duckx.hpp src/pugixml.hpp src/pugiconfig.hpp)
set(SOURCES src/duckx.cpp src/pugixml.cpp)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

if(BUILD_SHARED_LIBS)
    add_library(duckx SHARED ${HEADERS} ${SOURCES})
else()
    add_library(duckx STATIC ${HEADERS} ${SOURCES})
endif()

mark_as_advanced(CLEAR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR)

target_link_libraries(duckx zip)

install(
        TARGETS ${LIBRARY}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ${HEADERS} DESTINATION include)

add_executable(samples samples/sample1.cpp)
target_link_libraries(samples duckx)
add_executable(samples2 samples/sample2.cpp)
target_link_libraries(samples2 duckx)
