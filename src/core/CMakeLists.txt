
include_directories(.)

Y_CreateLibrary(y
    y
    y/check
    y/core
    y/system
)

add_subdirectory(tests)
