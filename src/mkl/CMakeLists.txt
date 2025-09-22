include_directories(. .. ../core)

Y_CreateLibrary(y-mkl
y/mkl
y/mkl/root
y/mkl/opt
y/mkl/tao
y/mkl/algebra
y/mkl/algebra/eigen
y/mkl/interpolation
y/mkl/derivatives
)

add_subdirectory(tests)
Y_Regression(mkl)
