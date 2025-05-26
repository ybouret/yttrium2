
include_directories(.)

Y_CreateLibrary(y
    y
    y/check
    y/ability
    y/core
    y/core/linked
    y/core/linked/list
    y/core/linked/pool
    y/system
    y/type
    y/ascii
    y/calculus
    y/concurrent
    y/concurrent/singleton
    y/memory
    y/memory/allocator
    y/memory/object
    y/memory/object/book
    y/utest
)

add_subdirectory(tests)
Y_Regression(core)






