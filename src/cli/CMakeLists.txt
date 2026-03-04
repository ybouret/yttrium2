
Y_Message("Command Line Interface programs")

include_directories(../core)
include_directories(../mkl)
include_directories(../chemical)
include_directories(../jive)
include_directories(../lua++)
include_directories(../y/lua/src)

macro(Y_CLI progname)
	message( STATUS "    CLI:    <${progname}>")
	add_executable(${progname} "${progname}.cpp")
	Y_LinkLibraries(${progname} "${ARGN}")
endmacro()

Y_CLI(y_trunc)
Y_CLI(y_embed)
Y_CLI(y_rgb)
if(APPLE)
	Y_CLI(y_mp_missing)
	#target_link_libraries(y_mp_missing y-jive)
endif()
Y_CLI(y_chemsys y-chemical y-json y-jive y-mkl y-lua++ y-lua)

