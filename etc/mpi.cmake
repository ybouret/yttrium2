# detection of MPI settings

set(MPI_FOUND OFF)
set(MPI_LIBRARIES "")

if(Y_ICC)
    set(MPICC "MPICC-NOTFOUND")
else()
    find_program(MPICC mpicc)
endif()

 
cmake_print_variables(MPICC)

if( "MPICC-NOTFOUND" STREQUAL "${MPICC}" )
    # Microsoft MPI ?
	set(MSMPI_INC "$ENV{MSMPI_INC}" )
	cmake_print_variables(MSMPI_INC)
	if( "" STREQUAL "${MSMPI_INC}")
		# no
	else()
		# yes
		set(MPI_FOUND ON)
		message( STATUS "found MSMPI")
		include_directories("${MSMPI_INC}")
		if(Y32)
			set(MSMPI_DIR "$ENV{MSMPI_LIB32}")
		else()
			set(MSMPI_DIR "$ENV{MSMPI_LIB64}")
		endif()
		cmake_print_variables(MSMPI_DIR)
		link_directories("${MSMPI_DIR}")
		set(MPI_LIBRARIES msmpi)
	endif()

else()
    set(MPI_FOUND ON)
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