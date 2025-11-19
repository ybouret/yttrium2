
#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"

#include "y/container/associative/hash/map.hpp"
#include "y/hashing/des64.hpp"
#include "y/system/rtti.hpp"

using namespace Yttrium;


Y_UTEST(excp)
{
    {
        const MPI::Exception excp(MPI_ERR_OTHER,"bad at %d", __LINE__);
        excp.show(std::cerr);
    }








}
Y_UDONE()

