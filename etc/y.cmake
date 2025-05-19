
################################################################################
##
##
## CMake Built-In Helpers
##
##
################################################################################
function(Y_Message)
	set(MSG "${ARGV}")
	string(LENGTH ${MSG} LEN)
	string( REPEAT "-" ${LEN} SEP)
	string( REPEAT " " ${LEN} SPC)
	message( STATUS )
	message( STATUS "/-"  ${SEP}  "-\\")
	message( STATUS "| "  ${SPC}  " |")
	message( STATUS "| "  ${ARGV} " |")
	message( STATUS "| "  ${SPC}  " |")
	message( STATUS "\\-" ${SEP}  "-/")
endfunction(Y_Message)

include(CMakePrintHelpers)
Y_Message("Project Settings")
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
Y_Message("Checking Compilers")

get_filename_component(Y_CC ${CMAKE_C_COMPILER} NAME_WE)
get_filename_component(Y_CXX ${CMAKE_CXX_COMPILER} NAME_WE)
cmake_print_variables(CMAKE_C_COMPILER)
cmake_print_variables(CMAKE_CXX_COMPILER)
cmake_print_variables(Y_CC)
cmake_print_variables(Y_CXX)
cmake_print_variables(CMAKE_BUILD_TYPE)

set(Y_CC_MAJOR 0)
set(Y_CC_MINOR 0)

function(Y_FIND_COMPILER_VERSION)
	message(STATUS "Find Compiler Version with [${ARGN}]")
	execute_process(COMMAND ${ARGN}
 	OUTPUT_VARIABLE THE_INFO)
	string( STRIP "${THE_INFO}" THE_INFO)
	string( REGEX REPLACE "[\r\n]+" ";" THE_INFO "${THE_INFO}")
	list(LENGTH THE_INFO NUM_INFO)
	if("${NUM_INFO}" STRLESS "1")
		message( FATAL_ERROR "Empty Compiler Output")
	endif()
	list(GET THE_INFO 0 THE_INFO)
	cmake_print_variables(THE_INFO)
endfunction()

if(OFF)
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
	cmake_print_variables(THE_INFO)
 	list(FIND THE_INFO "version" VPOS)
	cmake_print_variables(VPOS)
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
endif()

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
	Y_FIND_COMPILER_VERSION(${CMAKE_C_COMPILER} --version)
	list( APPEND CMAKE_C_FLAGS "-Wall -Wextra")
	list( APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++")
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
	Y_FIND_COMPILER_VERSION(${CMAKE_C_COMPILER} --version)
	list( APPEND CMAKE_C_FLAGS   "-Wall -Wextra")
	list( APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ ")
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
	Y_FIND_COMPILER_VERSION(${CMAKE_C_COMPILER} --version)
	list( APPEND CMAKE_C_FLAGS   "-Wall")
	list( APPEND CMAKE_CXX_FLAGS "-Wall")
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
	Y_FIND_COMPILER_VERSION(${CMAKE_C_COMPILER})
endif()


cmake_print_variables(CMAKE_C_FLAGS)
cmake_print_variables(CMAKE_CXX_FLAGS)

################################################################################
##
##
## Creating Library THE_LIB SUBDIRS=${ARGV}
##
##
################################################################################
function(Y_CreateLibrary THE_LIB)
	Y_Message("Create Library <${THE_LIB}>")
	set(SRC "")
	set(PRV "")
	set(HDR "")
	foreach(SUBDIR IN LISTS ARGN)
		message( STATUS "[${SUBDIR}]")
		file( GLOB src "${SUBDIR}/*.cpp")
		file( GLOB prv "${SUBDIR}/*.hxx")
		file( GLOB hdr "${SUBDIR}/*.hpp" "${SUBDIR}/*.h")
		source_group(${SUBDIR} FILES ${src} ${prv} ${hdr})
		list( APPEND SRC ${src})
		list( APPEND PRV ${prv})
		list( APPEND HDR ${hdr})
		install( FILES  ${hdr} DESTINATION include/${SUBDIR})
	endforeach()
	#cmake_print_variables(SRC)
	#cmake_print_variables(PRV)
	#cmake_print_variables(HDR)
	add_library(${THE_LIB} STATIC ${SRC} ${HDR} ${PRV})
	install( TARGETS ${THE_LIB} ARCHIVE)
endfunction()

function(Y_CreateTest THE_TEST)
	Y_MESSAGE("Create Test <${THE_TEST}>")
	# top-level sources
	set(SRC main.cpp)
	file( GLOB src "test-*.cpp")
	list( APPEND SRC ${src})
	add_executable(${THE_TEST} ${SRC})
endfunction()