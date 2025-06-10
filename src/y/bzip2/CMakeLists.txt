project(bzip2 C)

set(SRCS 
    blocksort.c
    huffman.c    
    crctable.c   
    randtable.c  
    compress.c  
    decompress.c 
    bzlib.c
)

add_definitions(-D_FILE_OFFSET_BITS=64)

add_library(y-bz2 STATIC ${SRCS})

add_executable(y_bzip2 bzip2.c)
target_link_libraries(y_bzip2 y-bz2)