
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;


Y_UTEST(excp)
{
    {
        const MPI::Exception excp(MPI_ERR_OTHER,"bad at %d", __LINE__);
        excp.show(std::cerr);
    }

}
Y_UDONE()

