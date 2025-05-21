
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
Y_Message("Checking Platforms")
cmake_print_variables(CMAKE_SYSTEM_NAME)

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

cmake_print_variables(CMAKE_C_COMPILER_VERSION)
string(REPLACE "." ";" Y_CC_VERSION ${CMAKE_C_COMPILER_VERSION})
list(GET Y_CC_VERSION 0 Y_CC_MAJOR)
list(GET Y_CC_VERSION 1 Y_CC_MINOR)
cmake_print_variables(Y_CC_MAJOR Y_CC_MINOR)

 

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
	string( APPEND CMAKE_C_FLAGS " -Wall -Wextra")
	string( APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Weffc++")
	if( "${Y_CC_MAJOR}" LESS "7" )
		string( APPEND CMAKE_CXX_FLAGS " -std=c++0x")
	endif()
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
	string( APPEND CMAKE_C_FLAGS   " -Wall -Wextra")
	string( APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Weffc++ -std=c++11")
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
	string( APPEND CMAKE_C_FLAGS   " -Wall")
	string( APPEND CMAKE_CXX_FLAGS " -Wall")
	if( "${Y_CC_MAJOR}" LESS_EQUAL "13" )
		string( APPEND CMAKE_CXX_FLAGS " -std=c++0x")
	endif()
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
	string( APPEND CMAKE_C_FLAGS " -Wall")
	string( APPEND CMAKE_CXX_FLAGS " -Wall -EHsc")
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
		message( STATUS "    [${SUBDIR}]")
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

	# sub-dir sources
	foreach(SUBDIR IN LISTS ARGN)
		message( STATUS "    [${SUBDIR}]")
		file( GLOB src "${SUBDIR}/*.cpp")
		list( APPEND SRC ${src})
		source_group(${SUBDIR} FILES ${src})
	endforeach()

	# gather
	add_executable(${THE_TEST} ${SRC})
	set(Y_Test ${THE_TEST} PARENT_SCOPE)
	add_custom_target("u${THE_TEST}" 
		COMMAND ${CMAKE_CTEST_COMMAND}
		DEPENDS ${THE_TEST}
		)
endfunction()

function(Y_UTEST THE_NAME)
	string(REPLACE ":" "_" THE_TEST "${THE_NAME}")
	add_test(${THE_NAME} ${Y_Test} ${THE_TEST} ${ARGN})
	message(STATUS "    <${THE_NAME}>")
endfunction()

 
