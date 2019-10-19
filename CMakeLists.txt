cmake_minimum_required(VERSION 3.0)

project(duckx VERSION 0.2)

option(BUILD_SHARED_LIBS "Build shared instead of static library" OFF)
option(BUILD_SAMPLE "Build provided sample" OFF)

set(HEADERS src/duckx.hpp src/zip.h src/miniz.h
     src/pugixml.hpp src/pugiconfig.hpp)
set(SOURCES src/duckx.cpp src/zip.c src/pugixml.cpp)

if(BUILD_SHARED_LIBS)
    add_library(duckx SHARED ${HEADERS} ${SOURCES})
else()
    add_library(duckx STATIC ${HEADERS} ${SOURCES})
endif()

mark_as_advanced(CLEAR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR)

if (BUILD_SAMPLE)
	# Sample executable
	set(SAMPLE_SOURCES samples/sample1.cpp)
	add_executable(duckx_sample ${SAMPLE_SOURCES})
	target_link_libraries(duckx_sample duckx)
endif()

install(
    TARGETS ${LIBRARY}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}${INSTALL_SUFFIX}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install(FILES ${HEADERS} DESTINATION include)

include_directories(src)

include(cmake/googletest.cmake)

fetch_googletest(
		${PROJECT_SOURCE_DIR}/cmake
		${PROJECT_BINARY_DIR}/googletest
)

enable_testing()
add_subdirectory(test)
