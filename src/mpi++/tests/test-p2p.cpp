
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(p2p)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    if(mpi.primary) std::cerr << "using " << mpi.callSign() << std::endl;
}
Y_UDONE()

