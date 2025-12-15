project(sqlite3 C)

Y_Message("Building SQLite3")
if(Y_MSC)
        string( APPEND CMAKE_C_FLAGS " -wd4711 -wd5045 -wd4242 -wd4820 -wd4668 -wd4191 -wd4574 -wd4255 -wd4090")
endif()

add_definitions(-DSQLITE_ENABLE_FTS4)
add_definitions(-DSQLITE_ENABLE_FTS5)
add_definitions(-DSQLITE_ENABLE_GEOPOLY)
add_definitions(-DSQLITE_ENABLE_MATH_FUNCTIONS)
add_definitions(-DSQLITE_ENABLE_PREUPDATE_HOOK)
add_definitions(-DSQLITE_ENABLE_RTREE)
add_definitions(-DSQLITE_ENABLE_SESSION)
add_definitions(-DSQLITE_THREADSAFE=1)

add_library(y-sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h)


