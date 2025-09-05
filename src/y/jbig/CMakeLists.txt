
if(Y_MSC)
	string( APPEND CMAKE_C_FLAGS " -wd4820 -wd4711 -wd4242 -wd4244 -wd4267 -wd4005 -wd4389 -wd4706 -wd5045 -wd4668 -wd4710 -wd4996 -wd4100")
endif()

add_library(y-jbig STATIC jbig.c jbig_ar.c)
add_library(y-jbig85 STATIC jbig85.c jbig_ar.c)

Y_ThirdParty(y-jbig)
Y_ThirdParty(y-jbig85)


add_executable(y_test_jbig tstcodec.c)
target_link_libraries(y_test_jbig y-jbig)

add_executable(y_test_jbig85 tstcodec85.c)
target_link_libraries(y_test_jbig85 y-jbig85)

add_custom_command(TARGET y_test_jbig POST_BUILD
COMMAND $<TARGET_FILE:y_test_jbig>
COMMENT "[Yttrium] Testing JBIG"
VERBATIM)

add_custom_command(TARGET y_test_jbig85 POST_BUILD
COMMAND $<TARGET_FILE:y_test_jbig85>
COMMENT "[Yttrium] Testing JBIG85"
VERBATIM)

 