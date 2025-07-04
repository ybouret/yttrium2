
Y_Message("Command Line Interface programs")

include_directories(../core)

macro(Y_CLI progname)
message( STATUS "    CLI:    <${progname}>")
add_executable(${progname} "${progname}.cpp")
Y_LinkLibraries(${progname})
endmacro()

Y_CLI(y_trunc)

