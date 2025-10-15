include_directories(. ../core)
add_library(spyndle MODULE spyndle.cpp)
Y_LinkLibraries(spyndle)
Y_CopyDLL(spyndle ${CMAKE_CURRENT_SOURCE_DIR}/spyndle${Y_DLL_UUID})
include(../../etc/python.cmake)

if(Y_Python)
    add_custom_command( TARGET spyndle POST_BUILD 
    COMMAND ${Python3_EXECUTABLE} spyndle.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM)
endif()
