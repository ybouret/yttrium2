
include_directories(.)

Y_CreateLibrary(y
    y
    y/check
    y/ability
    y/core
    y/core/linked
    y/core/linked/list
    y/core/linked/pool
    y/core/linked/convert
    y/system
    y/type
    y/ascii
    y/calculus
    y/concurrent
    y/concurrent/singleton
    y/container
    y/memory
    y/memory/workspace
    y/memory/allocator
    y/memory/object
    y/memory/object/book
    y/memory/object/factory
    y/memory/joint
    y/utest
    y/hashing
    y/xml
)

add_subdirectory(tests)
Y_Regression(core)






