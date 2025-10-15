Y_Message("Building IonoCell C++ for Python")


add_library(ionocell MODULE ionocell.cpp ionocell.hpp diffusion-coefficients.js)
Y_LinkLibraries(ionocell y-chemical y-json y-jive y-mkl y-lua++ y-lua)

set(ionocell_dll "ionocell${Y_DLL_UUID}")
Y_CopyDLL(ionocell ${CMAKE_CURRENT_SOURCE_DIR}/${ionocell_dll})

include(../../../etc/python.cmake)

if(Y_Python)
    add_custom_command( TARGET ionocell POST_BUILD 
    COMMAND ${Python3_EXECUTABLE} ionocell.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
endif()

add_custom_command( TARGET ionocell POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E tar cfvz ionocell.tgz ${ionocell_dll} ionocell.py spyndle.py
    COMMENT "Building Ionocell/Archive"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)