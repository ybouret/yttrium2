Y_CreateTest(test-mkl
root
tao
opt
algebra
interp
drvs
)
Y_LinkLibraries(test-mkl y-mkl)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(interval)
Y_UTEST(intervals)

Y_UTEST(root:zfind)
Y_UTEST(root:profile)

Y_UTEST(tao:1)

Y_UTEST(opt:parabolic)
Y_UTEST(opt:minimize)

Y_UTEST(algebra:lu)
Y_UTEST(algebra:adjoint)
Y_UTEST(algebra:ortho:space)
Y_UTEST(algebra:coven)
Y_UTEST(algebra:tridiag)
Y_UTEST(algebra:cyclic)
Y_UTEST(algebra:svd)

Y_UTEST(drvs1D)
Y_UTEST(drvsND)
