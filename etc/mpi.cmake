# detection of MPI settings

set(MPI_FOUND OFF)

find_program(MPICC mpicc)
 
cmake_print_variables(MPICC)

if( "MPICC-NOTFOUND" STREQUAL "${MPICC}" )
    
else()
    message( STATUS "found mpicc" )
    execute_process(COMMAND ${MPICC} --show
        RESULT_VARIABLE MPI_RES
        OUTPUT_VARIABLE MPI_OUT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    cmake_print_variables(MPI_RES MPI_OUT)
endif()