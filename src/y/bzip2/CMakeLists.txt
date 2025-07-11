project(bzip2 C)

Y_Message("Building bzip2")

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
if(Y_MSC)
	string( APPEND CMAKE_C_FLAGS " -wd4820 -wd4668 -wd4127 -wd4242 -wd4244 -wd4267 -wd4996 -wd5045 -wd4100 -wd4701 -wd4703 -wd4255 -wd4710")
endif()

add_library(y-bz2 STATIC ${SRCS})
Y_ThirdParty(y-bz2)



add_executable(bzip2 bzip2.c)
target_link_libraries(bzip2 y-bz2)

add_custom_command(TARGET bzip2 POST_BUILD
COMMAND bzip2  -1  < sample1.ref > sample1.rb2
COMMAND bzip2  -2  < sample2.ref > sample2.rb2
COMMAND bzip2  -3  < sample3.ref > sample3.rb2
COMMAND bzip2  -d  < sample1.bz2 > sample1.tst
COMMAND bzip2  -d  < sample2.bz2 > sample2.tst
COMMAND bzip2  -ds < sample3.bz2 > sample3.tst
COMMAND ${CMAKE_COMMAND} -E compare_files sample1.bz2 sample1.rb2 
COMMAND ${CMAKE_COMMAND} -E compare_files sample2.bz2 sample2.rb2
COMMAND ${CMAKE_COMMAND} -E compare_files sample3.bz2 sample3.rb2
COMMAND ${CMAKE_COMMAND} -E compare_files sample1.tst sample1.ref
COMMAND ${CMAKE_COMMAND} -E compare_files sample2.tst sample2.ref
COMMAND ${CMAKE_COMMAND} -E compare_files sample3.tst sample3.ref
COMMAND ${CMAKE_COMMAND} -E rm -f sample1.rb2 sample2.rb2 sample3.rb2
COMMAND ${CMAKE_COMMAND} -E rm -f sample1.tst sample2.tst sample3.tst
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
COMMENT           "Testing bzip2"
VERBATIM)
