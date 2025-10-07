include_directories(. ../core)

add_library(spyndle MODULE spyndle.cpp)
Y_LinkLibraries(spyndle)
Y_CopyDLL(spyndle ${CMAKE_CURRENT_SOURCE_DIR}/spyndle.dll)
