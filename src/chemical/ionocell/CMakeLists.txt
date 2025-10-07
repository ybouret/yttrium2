add_library(ionocell MODULE ionocell.cpp ionocell.hpp diffusion-coefficients.js)
Y_LinkLibraries(ionocell y-chemical y-json y-jive y-mkl y-lua++ y-lua)
Y_CopyDLL(ionocell ${CMAKE_CURRENT_SOURCE_DIR}/ionocell.dll)
