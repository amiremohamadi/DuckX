cmake_minimum_required(VERSION 3.0)

project(duckx VERSION 0.2)

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)

set(HEADERS src/duckx.hpp src/zip.h src/miniz.h
     src/pugixml.hpp src/pugiconfig.hpp)
set(SOURCES src/duckx.cpp src/zip.c src/pugixml.cpp)

if(BUILD_SHARED_LIBS)
    add_library(duckx SHARED ${HEADERS} ${SOURCES})
else()
    add_library(duckx STATIC ${HEADERS} ${SOURCES})
endif()

mark_as_advanced(CLEAR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR)


install(
    TARGETS ${LIBRARY}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(FILES ${HEADERS} DESTINATION include)
