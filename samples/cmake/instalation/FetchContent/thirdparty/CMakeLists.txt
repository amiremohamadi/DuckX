set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/libs" CACHE STRING "THIRDPARTY DIRECTORY")
set(FETCHCONTENT_QUIET OFF)
include(FetchContent)

FetchContent_Declare(
    Pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.15
)
FetchContent_Declare(
    DuckX
    GIT_REPOSITORY https://github.com/amiremohamadi/DuckX.git
    GIT_TAG v1.2.2
)
FetchContent_MakeAvailable(Pugixml DuckX)

message("DuckX SOURCE: ${duckx_SOURCE_DIR}")
message("DuckX BINARY: ${duckx_BINARY_DIR}")

message("pugixml SOURCE: ${pugixml_SOURCE_DIR}")
message("pugixml BINARY: ${pugixml_BINARY_DIR}")