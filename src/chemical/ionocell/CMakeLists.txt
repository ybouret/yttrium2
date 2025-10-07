add_library(ionocell MODULE ionocell.cpp ionocell.hpp diffusion-coefficients.js)
Y_LinkLibraries(ionocell y-chemical y-json y-jive y-mkl y-lua++ y-lua)


set(IONOCELL ${CMAKE_CURRENT_SOURCE_DIR}/ionocell.dll)

Y_DLL_COPY(ionocell ${IONOCELL})

if(FALSE)
add_custom_command( TARGET ionocell POST_BUILD 
COMMAND ${CMAKE_COMMAND} -E echo "Copy $<TARGET_FILE:ionocell>"
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ionocell> ${IONOCELL}
VERBATIM)


if(XCODE)
    add_custom_command( TARGET ionocell POST_BUILD 
    COMMAND codesign --remove-signature ${IONOCELL}
    COMMAND xcrun codesign -s - ${IONOCELL}
    VERBATIM)
endif()
endif()
