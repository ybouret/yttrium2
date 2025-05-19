cmake_minimum_required(VERSION 3.11)
project(yttrium2 C CXX)

set(Y_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set(Y_ETC_DIR ${Y_SRC_DIR}/../etc)
set(CMAKE_INSTALL_PREFIX ${Y_SRC_DIR}/../sdk)

include(${Y_ETC_DIR}/y.cmake)

find_program(DOX doxygen DOC "Doxygen")
cmake_print_variables(DOX)
if( "${DOX}" STREQUAL "DOX-NOTFOUND")
    message( STATUS "no doxygen")
else()
    message( STATUS "found ${DOX}")
    add_custom_target(dox ${DOX} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

add_subdirectory(core)

