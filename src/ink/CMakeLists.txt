include_directories(. .. ../core ../jive ../y/tiff/libtiff)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../y/jpeg)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../y/png)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../y/tiff/libtiff)


cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)

Y_CreateLibrary(y-ink
y/ink
y/ink/image
y/ink/image/format
y/ink/image/format/pnm
y/ink/ops
y/ink/filter
y/ink/draw
y/ink/histogram
y/ink/blur
)

add_dependencies(y-ink y-jpeg png_static tiff)

add_subdirectory(tests)
Y_Regression(ink)
