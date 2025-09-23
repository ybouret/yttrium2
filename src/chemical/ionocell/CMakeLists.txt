add_library(ionocell MODULE ionocell.cpp ionocell.hpp)
Y_LinkLibraries(ionocell y-chemical y-jive y-mkl y-lua++ y-lua)


#add_custom_command( TARGET typyc POST_BUILD 
#COMMAND ${CMAKE_COMMAND} -E echo "Copy $<TARGET_FILE:typyc>"
#COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:typyc> ${CMAKE_CURRENT_SOURCE_DIR}/typyc.so
#VERBATIM)
