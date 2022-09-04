set(ZIP_PREFIX zip0121)
set(ZIP_URL https://github.com/kuba--/zip/archive/refs/tags/v0.1.21.zip)

ExternalProject_Add(
        ${ZIP_PREFIX}
        PREFIX ${ZIP_PREFIX}
        URL ${ZIP_URL}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND cmake .
        BUILD_COMMAND  make -j
        INSTALL_COMMAND ""
        LOG_DOWNLOAD 1
        LOG_BUILD 1
)

set(ZIP_INCLUDE ${CMAKE_BINARY_DIR}/${ZIP_PREFIX}/src/${ZIP_PREFIX}/src)
set(ZIP_LIB ${CMAKE_BINARY_DIR}/${ZIP_PREFIX}/src/${ZIP_PREFIX}/libzip.a)
