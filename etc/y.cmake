
################################################################################
##
##
## CMake Built-In Helpers
##
##
################################################################################
macro(Y_MESSAGE)
	message(STATUS "---------------------------------------------------------" )
	message(STATUS ${ARGV})
	message(STATUS "---------------------------------------------------------" )
endmacro(Y_MESSAGE)

include(CMakePrintHelpers)
Y_MESSAGE("Project Settings")
cmake_print_variables(PROJECT_SOURCE_DIR)
cmake_print_variables(CMAKE_GENERATOR)

################################################################################
##
##
## Detecting the CMAKE_BUILD_TYPE
##
##
################################################################################
if("" STREQUAL "${CMAKE_BUILD_TYPE}")
	set(CMAKE_BUILD_TYPE "Debug")
endif()

# selecting build type
set(Y_DEBUG   TRUE)
set(Y_RELEASE FALSE)
set(Y_BUILD_TYPE_IS_DEFINED FALSE)

if( "Debug" STREQUAL "${CMAKE_BUILD_TYPE}") 
	# default
	set(Y_BUILD_TYPE_IS_DEFINED TRUE)
endif()

if( "Release" STREQUAL "${CMAKE_BUILD_TYPE}")
	# release
	set(Y_BUILD_TYPE_IS_DEFINED TRUE)
	set(Y_DEBUG FALSE)
	set(Y_RELEASE TRUE)
endif()

if(NOT Y_BUILD_TYPE_IS_DEFINED)
	message( FATAL_ERROR "CMAKE_BUILD_TYPE!=[Debug|Release]")
endif()


################################################################################
##
##
## Checking Platforms
##
##
################################################################################

################################################################################
##
##
## Checking Compilers
##
##
################################################################################
Y_MESSAGE("Checking Compilers")
cmake_print_variables(CMAKE_C_COMPILER)
cmake_print_variables(CMAKE_CXX_COMPILER)
get_filename_component(Y_CC ${CMAKE_C_COMPILER} NAME_WE)
get_filename_component(Y_CXX ${CMAKE_CXX_COMPILER} NAME_WE)
cmake_print_variables(Y_CC Y_CXX CMAKE_BUILD_TYPE)

set(Y_CC_MAJOR 0)
set(Y_CC_MINOR 0)


function(Y_FIND_COMPILER_VERSION)
	# execute command to extract some version
	#cmake_print_variables(ARGN)
	#cmake_print_variables(ARGC)
	if( "0" STREQUAL "${ARGC}")
		execute_process(COMMAND ${CMAKE_C_COMPILER}
			OUTPUT_VARIABLE THE_OUT	ERROR_VARIABLE  THE_ERR)
	endif()
	if( "1" STREQUAL "${ARGC}")
		#Y_MESSAGE("with one arg")
		execute_process(COMMAND ${CMAKE_C_COMPILER} ${ARGV0}
			OUTPUT_VARIABLE THE_OUT	ERROR_VARIABLE  THE_ERR)
	endif()
	set(THE_INFO "${THE_OUT}${THE_ERR}")
	string( STRIP "${THE_INFO}" THE_INFO)
	# transform output into list of words
	string( REGEX REPLACE "[^A-Za-z0-9.]+" ";" THE_INFO "${THE_INFO}")
 	list(FIND THE_INFO "version" VPOS)
	if( "-1" STREQUAL "${VPOS}")
		message( FATAL_ERROR "couldn't find 'version' from '${Y_CC}'")
	endif()
	# extract version string from after the 'version' word
	math(EXPR VPOS "${VPOS}+1")
	list(GET THE_INFO ${VPOS} Y_CC_VERSION)
	string( REPLACE "." ";" Y_CC_VERSION "${Y_CC_VERSION}")
 	list(GET Y_CC_VERSION 0 MAJOR)
	list(GET Y_CC_VERSION 1 MINOR)
	set(Y_CC_MAJOR ${MAJOR} PARENT_SCOPE)
	set(Y_CC_MINOR ${MINOR} PARENT_SCOPE)
	cmake_print_variables(MAJOR MINOR)
endfunction()

set(Y_KNOWN_COMPILER FALSE)

################################################################################
#
# configuration for gcc/g++
#
################################################################################
if("${Y_CC}" MATCHES "gcc.*")
	message( STATUS "Using GNU Compilers")
	set(Y_KNOWN_COMPILER TRUE)
	set(Y_GNU TRUE)
	Y_FIND_COMPILER_VERSION(-v)
endif()

################################################################################
#
# configuration for clang/clang++
#
################################################################################
if("${Y_CC}" MATCHES "clang.*")
	message( STATUS "Using Clang Compilers")
	set(Y_KNOWN_COMPILER TRUE)
	set(Y_CLANG TRUE)
	Y_FIND_COMPILER_VERSION(-v)
endif()


################################################################################
#
# configuration for icc/icpc
#
################################################################################
if("${Y_CC}" MATCHES "icc.*")
	message( STATUS "Using Intel Compilers")
	set(Y_KNOWN_COMPILER TRUE)
	set(Y_ICC TRUE)
	Y_FIND_COMPILER_VERSION(-v)
endif()

################################################################################
#
# configuration for Microsoft
#
################################################################################
if("${Y_CC}" STREQUAL "cl")
	message( STATUS "Using Microsoft Compilers")
	set(Y_KNOWN_COMPILER TRUE)
	set(Y_MSC TRUE)
	Y_FIND_COMPILER_VERSION()
endif()

