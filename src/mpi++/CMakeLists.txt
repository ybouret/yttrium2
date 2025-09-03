include_directories(. .. ../core)
include(${CMAKE_CURRENT_SOURCE_DIR}/../../etc/mpi.cmake)

if(MPI_FOUND)
    #Y_CreateLibrary(y-json y/json)

    add_subdirectory(tests)
    #Y_Regression(json)
endif()