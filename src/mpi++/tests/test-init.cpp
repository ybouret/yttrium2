
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(init)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    Y_MPI_ForEach(mpi,mpi.display(std::cerr,0) );
}
Y_UDONE()

