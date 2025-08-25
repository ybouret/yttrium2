cmake_minimum_required(VERSION 3.11)
project(yttrium2 C CXX)

set(Y_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set(Y_ETC_DIR ${Y_SRC_DIR}/../etc)
set(CMAKE_INSTALL_PREFIX ${Y_SRC_DIR}/../sdk)

include(${Y_ETC_DIR}/y.cmake)
Y_Message("Welcome to Yttrium!")

find_program(DOX doxygen DOC "Doxygen")
cmake_print_variables(DOX)
if( "${DOX}" STREQUAL "DOX-NOTFOUND")
    message( STATUS "no doxygen")
else()
    message( STATUS "found ${DOX}")
    add_custom_target(dox ${DOX} -q WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

set(Y_UnitTests "")
add_subdirectory(core)
add_subdirectory(mkl)
add_subdirectory(jive)
add_subdirectory(chemical)
add_subdirectory(json)
add_subdirectory(ink)
cmake_print_variables(Y_UnitTests)

add_subdirectory(y)
add_subdirectory(cli)

if( NOT "" STREQUAL "${Y_UnitTests}")
    add_custom_target(regression 
    DEPENDS ${Y_UnitTests})
endif()

Y_Message("Yttrium is now ready to be built!")
