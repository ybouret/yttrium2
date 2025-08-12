add_library(y-jbig STATIC jbig.c jbig_ar.c)
add_library(y-jbig85 STATIC jbig85.c jbig_ar.c)

add_executable(y_test_jbig tstcodec.c)
target_link_libraries(y_test_jbig y-jbig)

add_executable(y_test_jbig85 tstcodec85.c)
target_link_libraries(y_test_jbig85 y-jbig85)

if(true)

    add_custom_command(TARGET y_test_jbig POST_BUILD
    COMMAND $<TARGET_FILE:y_test_jbig>
    COMMENT "[Yttrium] Testing JBIG"
    VERBATIM)

    add_custom_command(TARGET y_test_jbig85 POST_BUILD
    COMMAND $<TARGET_FILE:y_test_jbig85>
    COMMENT "[Yttrium] Testing JBIG85"
    VERBATIM)

endif()