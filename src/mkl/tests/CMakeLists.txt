Y_CreateTest(test-mkl
root)
Y_LinkLibraries(test-mkl)

enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(root:zbis)

