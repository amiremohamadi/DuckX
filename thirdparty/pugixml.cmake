set(PUGIXML_PREFIX pugixml19)
set(PUGIXML_URL https://github.com/zeux/pugixml/releases/download/v1.9/pugixml-1.9.tar.gz)

ExternalProject_Add(
        ${PUGIXML_PREFIX}
        PREFIX ${PUGIXML_PREFIX}
        URL ${PUGIXML_URL}
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND cmake .
        BUILD_COMMAND  make -j
        INSTALL_COMMAND ""
        LOG_DOWNLOAD 1
        LOG_BUILD 1
)

set(PUGIXML_INCLUDE ${CMAKE_BINARY_DIR}/${PUGIXML_PREFIX}/src/${PUGIXML_PREFIX}/src)
set(PUGIXML_LIB ${CMAKE_BINARY_DIR}/${PUGIXML_PREFIX}/src/${PUGIXML_PREFIX}/libpugixml.a)
