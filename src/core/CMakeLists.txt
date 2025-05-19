
include_directories(.)

Y_CreateLibrary(y
    y
    y/check
    y/core
    y/system
    y/utest
)

add_subdirectory(tests)
