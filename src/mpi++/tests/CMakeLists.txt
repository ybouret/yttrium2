Y_CreateTest(test-mpi++)
Y_LinkLibraries(test-mpi++ y-mpi++ ${MPI_LIBRARIES})
#target_link_libraries(test-mpi++ y-mpi++ ${MPI_LIBRARIES})
enable_testing()

Y_Message("Preparing ${Y_Test}")

Y_UTEST(excp) 
Y_UTEST(init)
Y_UTEST(p2p)
