Y_CreateTest(test-mpi++)
Y_LinkLibraries(test-mpi++)

enable_testing()

Y_Message("Preparing ${Y_Test}")
 
Y_UTEST(init)
