
include_directories(../core)

macro(Y_CLI progname)
add_executable(${progname} "${progname}.cpp")
target_link_libraries(${progname} y)
endmacro()

Y_CLI(y_trunc)

