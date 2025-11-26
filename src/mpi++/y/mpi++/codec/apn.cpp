
#include "y/mpi++/api.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{
    template <>
    void MPI::Codec<apn>::Send(MPI          & mpi,
                               const apn    & n,
                               const size_t   target,
                               const int      tag)
    {
        Y_Lock(*n);
        const size_t sz = n.bytes();
        mpi.sendCount(sz,target,tag);
        if(sz>0)
        {

        }
    }


}
