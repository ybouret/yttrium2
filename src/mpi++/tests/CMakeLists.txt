Y_CreateTest(test-mpi++)
Y_LinkLibraries(test-mpi++)
target_link_libraries(test-mpi++ y-mpi++ ${MPI_LIBRARIES})
enable_testing()

Y_Message("Preparing ${Y_Test}")
 
Y_UTEST(init)
