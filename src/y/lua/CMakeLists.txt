project(y-lua C)

Y_Message("Building Lua")

# where source code is
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#include_directories(${SRC})

# from src/Makefile
set(LUA_O lapi.o lcode.o lctype.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o lundump.o lvm.o lzio.o
lauxlib.o lbaselib.o lcorolib.o ldblib.o liolib.o lmathlib.o loadlib.o loslib.o lstrlib.o ltablib.o lutf8lib.o linit.o)

cmake_print_variables(LUA_O)
set(LUA_C)
foreach(file_o IN LISTS LUA_O)
    string( REPLACE ".o" ".c" file_c "${file_o}")
    message( STATUS ${file_c} )
    list( APPEND LUA_C "src/${file_c}")
endforeach()
#string( REPLACE ".o" ".c" LUA_C "${LUA_O}" )
cmake_print_variables(LUA_C)

add_library( y-lua STATIC ${LUA_C} )
Y_ThirdParty(y-lua)

add_executable(lua src/lua.c)
target_link_libraries(lua y-lua)