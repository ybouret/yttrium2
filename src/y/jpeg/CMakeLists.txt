project(jpeg C)

if(Y_MSC)
	string( APPEND CMAKE_C_FLAGS " -wd4820 -wd4100 -wd4711 -wd4996 -wd4774 -wd4710 -wd5045 -wd4127 -wd4702 -wd4061")
endif()

set(HERE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(jconfig.txt jconfig.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(LIBSOURCES
jaricom.c jcapimin.c jcapistd.c jcarith.c jccoefct.c jccolor.c 
 jcdctmgr.c jchuff.c jcinit.c jcmainct.c jcmarker.c jcmaster.c 
 jcomapi.c jcparam.c jcprepct.c jcsample.c jctrans.c jdapimin.c 
 jdapistd.c jdarith.c jdatadst.c jdatasrc.c jdcoefct.c jdcolor.c 
 jddctmgr.c jdhuff.c jdinput.c jdmainct.c jdmarker.c jdmaster.c 
 jdmerge.c jdpostct.c jdsample.c jdtrans.c jerror.c jfdctflt.c 
 jfdctfst.c jfdctint.c jidctflt.c jidctfst.c jidctint.c jquant1.c 
 jquant2.c jutils.c jmemmgr.c)
        

add_library(y-jpeg STATIC jmemnobs.c ${LIBSOURCES})
Y_ThirdParty(y-jpeg)


set(CSOURCES cjpeg.c rdppm.c rdgif.c rdtarga.c rdrle.c rdbmp.c rdswitch.c cdjpeg.c)
add_executable(y_cjpeg ${CSOURCES})
target_link_libraries(y_cjpeg y-jpeg)

set(DSOURCES djpeg.c wrppm.c wrgif.c wrtarga.c wrrle.c wrbmp.c rdcolmap.c cdjpeg.c)

add_executable(y_djpeg ${DSOURCES})
target_link_libraries(y_djpeg y-jpeg)

set(TRSOURCES  jpegtran.c rdswitch.c cdjpeg.c transupp.c)
add_executable(y_jpegtran ${DSOURCES})
target_link_libraries(y_jpegtran y-jpeg)

#add_executable(y_rdjpgcom rdjpgcom.c)
#target_link_libraries(y_rdjpgcom y-jpeg)

#add_executable(y_wrjpgcom wrjpgcom.c)
#target_link_libraries(y_wrjpgcom y-jpeg)

add_custom_command(TARGET y_djpeg POST_BUILD
    COMMAND y_djpeg -dct int -ppm             -outfile testout.ppm testorig.jpg
    COMMAND y_djpeg -dct int -gif             -outfile testout.gif testorig.jpg
    COMMAND y_djpeg -dct int -bmp -colors 256 -outfile testout.bmp testorig.jpg
    COMMAND y_djpeg -dct int -ppm             -outfile testoutp.ppm testprog.jpg
    COMMAND ${CMAKE_COMMAND} -E compare_files testimg.ppm  testout.ppm
    COMMAND ${CMAKE_COMMAND} -E compare_files testimg.gif  testout.gif
    COMMAND ${CMAKE_COMMAND} -E compare_files testimg.bmp  testout.bmp
    COMMAND ${CMAKE_COMMAND} -E compare_files testimgp.jpg testoutp.jpg
    WORKING_DIRECTORY ${HERE}
    COMMENT "Testing DJPEG"
    VERBATIM
)

add_custom_command(TARGET y_cjpeg POST_BUILD
    COMMAND y_cjpeg -dct int                   -outfile testout.jpg  testimg.ppm
    COMMAND y_cjpeg -dct int -progressive -opt -outfile testoutp.jpg testimg.ppm
    COMMAND ${CMAKE_COMMAND} -E compare_files testimg.jpg testout.jpg
    COMMAND ${CMAKE_COMMAND} -E compare_files testimgp.jpg testoutp.jpg
    WORKING_DIRECTORY ${HERE}
    COMMENT "Testing CJPEG"
    VERBATIM
)

add_custom_command(TARGET y_jpegtran POST_BUILD
    COMMAND y_jpegtran -outfile testoutt.jpg testprog.jpg
    #COMMAND ${CMAKE_COMMAND} -E compare_files testorig.jpg testoutt.jpg
    WORKING_DIRECTORY ${HERE}
    COMMENT "Testing JPEGTRAN"
    VERBATIM
)

