include_directories(. ../core)

add_library(spyndle MODULE spyndle.cpp)
Y_LinkLibraries(spyndle)

set(SPYNDLE ${CMAKE_CURRENT_SOURCE_DIR}/spyndle.dll)
add_custom_command( TARGET spyndle POST_BUILD 
COMMAND ${CMAKE_COMMAND} -E echo "Copy $<TARGET_FILE:spyndle>"
COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:spyndle> ${SPYNDLE}
VERBATIM)
