cmake_minimum_required(VERSION 3.11)
project(yttrium2 C CXX)

set(Y_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set(Y_ETC_DIR ${Y_SRC_DIR}/../etc)

include(${Y_ETC_DIR}/y.cmake)

add_subdirectory(core)

