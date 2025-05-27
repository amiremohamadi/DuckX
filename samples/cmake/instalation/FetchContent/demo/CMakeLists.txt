add_executable(demo App/App.cpp)


#duckX linkage
target_include_directories(demo PRIVATE "${duckx_SOURCE_DIR}/src" )
target_link_libraries(demo PRIVATE duckx)