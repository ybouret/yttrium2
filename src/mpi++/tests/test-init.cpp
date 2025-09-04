
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(init)
{
    //MPI & mpi = MPI::Init(&argc,&argv);


    //mpi.display(std::cerr,0);

    MPI_Init(&argc,&argv);

    MPI_Finalize();

}
Y_UDONE()

