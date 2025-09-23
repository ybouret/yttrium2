add_library(ionocell MODULE ionocell.cpp ionocell.hpp)
Y_LinkLibraries(ionocell y-chemical y-jive y-mkl y-lua++ y-lua)


if(XCODE)
    message( STATUS "Force Signing Library" )
    #add_custom_command( TARGET ionocell POST_BUILD 
    #COMMAND xcrun codesign -s - $<TARGET_FILE:ionocell>
    #VERBATIM)
endif()

add_custom_command( TARGET ionocell POST_BUILD 
COMMAND ${CMAKE_COMMAND} -E echo "Copy $<TARGET_FILE:ionocell>"
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ionocell> ${CMAKE_CURRENT_SOURCE_DIR}/ionocell.dll
VERBATIM)
