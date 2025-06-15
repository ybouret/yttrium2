
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
    y/system/wall-time
    y/type
    y/ascii
    y/calculus
    y/concurrent
    y/concurrent/windows
    y/concurrent/singleton
    y/concurrent/mutex
    y/concurrent/thread
    y/concurrent/data
    y/container
    y/container/iter
    y/container/algorithm
    y/container/sequence
    y/container/cxx
    y/container/ordered
    y/static
    y/static/workspace
    y/memory
    y/memory/allocator
    y/memory/small
    y/memory/small/ledger
    y/memory/joint
    y/memory/io
    y/memory/buffer
    y/object
    y/utest
    y/hashing
    y/xml
    y/stream/
    y/stream/io
    y/stream/libc
    y/stream/libc/file
    y/stream/memory
    y/sorting
    y/threading
    y/pointer
    y/information
    y/information/bwt
)

add_subdirectory(tests)
Y_Regression(core)






