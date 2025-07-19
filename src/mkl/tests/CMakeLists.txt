Y_CreateTest(test-mkl
root
tao
opt)
Y_LinkLibraries(test-mkl y-mkl)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(root:zfind)

Y_UTEST(tao:1)

Y_UTEST(opt:parabolic)
