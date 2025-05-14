
# helpers
include(CMakePrintHelpers)
message( STATUS "Project Settings" )
cmake_print_variables(PROJECT_SOURCE_DIR)
cmake_print_variables(CMAKE_GENERATOR)

if("" STREQUAL "${CMAKE_BUILD_TYPE}")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

cmake_print_variables(CMAKE_BUILD_TYPE)
# selecting build type
set(Y_DEBUG TRUE)
set(Y_RELEASE FALSE)
set(Y_BUILD_TYPE_DEFINED FALSE)

if( "Debug" STREQUAL "${CMAKE_BUILD_TYPE}") 
	# default
	set(Y_BUILD_TYPE_DEFINED TRUE)
endif()

if( "Release" STREQUAL "${CMAKE_BUILD_TYPE}")
	# release
	set(Y_BUILD_TYPE_DEFINED TRUE)
	set(Y_DEBUG FALSE)
	set(Y_RELEASE TRUE)
endif()

if(NOT Y_BUILD_TYPE_DEFINED)
	message( FATAL_ERROR "CMAKE_BUILD_TYPE!=[Debug|Release]")
endif()

# compiler
cmake_print_variables(CMAKE_C_COMPILER)
cmake_print_variables(CMAKE_CXX_COMPILER)
get_filename_component(Y_CC ${CMAKE_C_COMPILER} NAME_WE)
get_filename_component(Y_CXX ${CMAKE_CXX_COMPILER} NAME_WE)
cmake_print_variables(Y_CC Y_CXX)

macro(Y_FIND_COMPILER_VERSION)
	execute_process(
		COMMAND ${CMAKE_C_COMPILER} -v
		OUTPUT_VARIABLE THE_OUT
		ERROR_VARIABLE  THE_ERR
	)
	set(THE_INFO "${THE_OUT}${THE_ERR}")
	string( STRIP "${THE_INFO}" THE_INFO)
	string( REGEX REPLACE "[\r\n ]+" ";" THE_INFO "${THE_INFO}")
	list(FIND THE_INFO "version" VPOS)
	if( "-1" STREQUAL "${VPOS}")
		message( FATAL_ERROR "couldn't find 'version' from '${Y_CC}'")
	endif()
	math(EXPR VPOS "${VPOS}+1")
	list(GET THE_INFO ${VPOS} THE_VERSION)
	cmake_print_variables(THE_VERSION)
endmacro()

Y_FIND_COMPILER_VERSION()

