
include_directories(.)

Y_CreateLibrary(y
    y
    y/check
    y/ability
    y/core
    y/core/linked
    y/system
    y/type
    y/ascii
    y/calculus
    y/concurrent
    y/concurrent/singleton
    y/memory
    y/utest
)

add_subdirectory(tests)

