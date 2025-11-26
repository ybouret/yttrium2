


#include "y/mpi++/api.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{


    template <>
    void MPI::Codec<apq>::Send(MPI          & mpi,
                               const apq    & q,
                               const size_t   target,
                               const int      tag)
    {

        mpi.send1(q.numer,target,tag);
        mpi.send1(q.denom,target,tag);

    }

    template <>
    apq MPI::Codec<apq>::Recv(MPI &mpi, const size_t source, const int tag)
    {

        const apz numer = mpi.recv1<apz>(source,tag);
        const apn denom = mpi.recv1<apn>(source,tag);
        return apq(numer,denom);
    }




}
