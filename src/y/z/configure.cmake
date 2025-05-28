message( STATUS "configuring zlib")
set(ZLIB_VERSION "1.3.1")
set(ZLIB_ROOT    "zlib-${ZLIB_VERSION}")
set(ZLIB_TGZ     "${ZLIB_ROOT}.tar.gz")
set(ZLIB_URL     "https://www.zlib.net/${ZLIB_TGZ}")

set(ZLIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${ZLIB_ROOT}")
if (NOT EXISTS "${ZLIB_TGZ}")
    message( STATUS "downloading ${ZLIB_URL}")
    file( DOWNLOAD "${ZLIB_URL}" "${ZLIB_TGZ}"
    SHOW_PROGRESS
    EXPECTED_HASH SHA256=9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23)
endif()

if(NOT EXISTS "${ZLIB_PATH}")
    message(STATUS "extracting ${ZLIB_ROOT}")
    #file( ARCHIVE_EXTRACT INPUT "${ZLIB_TGZ}" LIST_ONLY)
    file( ARCHIVE_EXTRACT INPUT "${ZLIB_TGZ}" DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
endif()
