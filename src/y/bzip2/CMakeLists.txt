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

add_executable(bzip2 bzip2.c)
target_link_libraries(bzip2 y-bz2)

if(OFF)

set(Y_Shell "$ENV{SHELL}")
cmake_print_variables(Y_Shell)
get_filename_component(Y_SID "${Y_Shell}" NAME_WE)
cmake_print_variables(Y_SID)

add_custom_command(TARGET bzip2
POST_BUILD
USES_TERMINAL
COMMAND "${SHELL}" ARGS "-c '$<TARGET_NAME:bzip2> -1  < sample1.ref > sample1.rb2'"
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
COMMENT "Testing bzip2"
VERBATIM
)
endif()