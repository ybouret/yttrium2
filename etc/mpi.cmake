# detection of MPI settings

set(MPI_FOUND OFF)
set(MPI_LIBRARIES "")

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
    cmake_print_variables(MPI_OUT)
    string(REGEX REPLACE " +"  ";" MPI_OUT "${MPI_OUT}")
    cmake_print_variables(MPI_OUT)
    foreach(arg IN LISTS MPI_OUT)
        #message( STATUS "${arg}" )

        if(${arg} MATCHES "^-I.*")
            #message( STATUS "include : ${arg}" )
            string(SUBSTRING ${arg} 2 -1 arg)
            message( STATUS "include : ${arg}" )
            include_directories(${arg})
        endif()

         if(${arg} MATCHES "^-L.*")
            string(SUBSTRING ${arg} 2 -1 arg)
            message( STATUS "libpath : ${arg}" )
            link_directories(${arg})
        endif()

         if(${arg} MATCHES "^-l.*")
            string(SUBSTRING ${arg} 2 -1 arg)
            message( STATUS "library : ${arg}" )
            #link_directories(${arg})
            list( APPEND MPI_LIBRARIES ${arg})
        endif()

    endforeach()
    
    cmake_print_variables(MPI_LIBRARIES)

endif()