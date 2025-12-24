include_directories(. .. ../core)

Y_CreateLibrary(y-mkl
y/mkl
y/mkl/root
y/mkl/opt
y/mkl/tao
y/mkl/tao/broker
y/mkl/algebra
y/mkl/algebra/eigen
y/mkl/interpolation
y/mkl/derivatives
y/mkl/ode
y/mkl/ode/explicit
y/mkl/fit
y/mkl/fit/type
y/mkl/fit/adjustable
y/mkl/fit/spec
y/mkl/statistics
y/mkl/io
)

add_subdirectory(tests)
Y_Regression(mkl)
