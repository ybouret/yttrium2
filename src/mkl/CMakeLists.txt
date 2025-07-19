include_directories(. .. ../core)

Y_CreateLibrary(y-mkl
y/mkl
y/mkl/root
y/mkl/opt
y/mkl/tao
)

add_subdirectory(tests)
Y_Regression(mkl)
