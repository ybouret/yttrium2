include_directories(. .. ../core)

Y_CreateLibrary(y-mkl
y/mkl
y/mkl/root
)

add_subdirectory(tests)
Y_Regression(mkl)
