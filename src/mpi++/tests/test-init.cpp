
#include "y/utest/run.hpp"
#include <mpi.h>

using namespace Yttrium;

Y_UTEST(init)
{
    MPI_Init(&argc, &argv);
    
    MPI_Finish();
}
Y_UDONE()

