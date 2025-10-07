find_package(Python3 COMPONENTS Interpreter)

if(Python3_Interpreter_FOUND)
    set(Y_Python ON)
    message( STATUS "Found Python @'${Python3_EXECUTABLE}'")
else()
    set(Y_Python OFF)
    message( STATUS "No Python Interpreter" )
endif()