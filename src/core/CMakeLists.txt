
include_directories(.)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/../y/zlib)

#cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)
#message( FATAL_ERROR "stop" )

Y_CreateLibrary(y
    y
    y/format
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
    y/ascii/convert
    y/utf8
    y/calculus
    y/concurrent
    y/concurrent/windows
    y/concurrent/singleton
    y/concurrent/mutex
    y/concurrent/thread
    y/concurrent/data
    y/container
    y/container/matrix
    y/container/iter
    y/container/algorithm
    y/container/sequence
    y/container/cxx
    y/container/ordered
    y/container/tree
    y/container/associative
    y/container/associative/suffix
    y/container/associative/hash
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
    y/hashing/key
    y/xml
    y/stream/
    y/stream/io
    y/stream/libc
    y/stream/libc/file
    y/stream/memory
    y/stream/proc
    y/stream/gzip
    y/stream/gzip/file
    y/sorting
    y/threading
    y/pointer
    y/information
    y/information/bwt
    y/information/stream
    y/protean
    y/protean/node
    y/protean/cache
    y/protean/proto
    y/protean/bare
    y/protean/bare/light
    y/protean/bare/heavy
    y/protean/solo
    y/protean/solo/light
    y/protean/solo/heavy
    y/protean/coop
    y/protean/coop/light
    y/protean/coop/heavy
    y/string
    y/string/stride
    y/apex
    y/apex/m
    y/apex/k
    y/apex/k/parcel
    y/apex/k/device
    y/apex/block
    y/apex/block/model
    y/apex/n
    y/apex/z
    y/apex/q
    y/apex/api/ortho
    y/apex/api/coven
    y/mkl
    y/mkl/api
    y/random
    y/cameo
    y/cameo/genus
    y/cameo/summator
    y/cameo/multiplier
    y/cameo/multiplier/synod
    y/functor
    y/dft
    y/dft/fmt
    y/vfs
    y/vfs/local
    y/counting
    y/counting/c
    y/graphviz
)

add_subdirectory(tests)
Y_Regression(core)






