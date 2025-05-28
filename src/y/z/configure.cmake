message( STATUS "configuring zlib")
set(ZLIB_VERSION "1.3.1")
set(ZLIB_ROOT    "zlib-${ZLIB_VERSION}")
set(ZLIB_TGZ     "${ZLIB_ROOT}.tar.gz")
set(ZLIB_URL     "https://www.zlib.net/${ZLIB_TGZ}")

if (NOT EXISTS "${ZLIB_TGZ}")
    file( DOWNLOAD "${ZLIB_URL}" "${ZLIB_TGZ}"
    SHOW_PROGRESS
    EXPECTED_HASH SHA256=9a93b2b7dfdac77ceba5a558a580e74667dd6fede4585b91eefb60f03b72df23)
endif()