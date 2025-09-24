include_directories(. ../core)
add_library(typyc MODULE typyc.cpp)
Y_LinkLibraries(typyc)

set(TYPYC ${CMAKE_CURRENT_SOURCE_DIR}/typyc.so)
add_custom_command( TARGET typyc POST_BUILD 
COMMAND ${CMAKE_COMMAND} -E echo "Copy $<TARGET_FILE:typyc>"
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:typyc> ${TYPYC}
VERBATIM)

#if(XCODE)
if(FALSE)
    add_custom_command( TARGET typyc POST_BUILD 
    COMMAND xcrun codesign -s - ${TYPYC}
    VERBATIM)
endif()
