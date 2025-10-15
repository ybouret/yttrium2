Y_Message("Building IonoCell C++ for Python")


add_library(ionocell MODULE ionocell.cpp ionocell.hpp diffusion-coefficients.js)
Y_LinkLibraries(ionocell y-chemical y-json y-jive y-mkl y-lua++ y-lua)
Y_CopyDLL(ionocell ${CMAKE_CURRENT_SOURCE_DIR}/ionocell${Y_DLL_UUID})

include(../../../etc/python.cmake)

if(Y_Python)
    add_custom_command( TARGET ionocell POST_BUILD 
    COMMAND ${Python3_EXECUTABLE} ionocell.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
endif()