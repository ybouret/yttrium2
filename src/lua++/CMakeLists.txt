

include_directories(. ../core ../y/lua/src)

#add_definitions("-DLUA_C89_NUMBERS")

Y_CreateLibrary(y-lua++
y/lua++
)

add_subdirectory(tests)
Y_Regression(lua++)

