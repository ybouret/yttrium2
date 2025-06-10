project(bzip2 C)

Y_Message("bzip2")

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

set(Y_Shell "$ENV{SHELL}")
cmake_print_variables(Y_Shell)
get_filename_component(Y_SID "${Y_Shell}" NAME_WE)
cmake_print_variables(Y_SID)
