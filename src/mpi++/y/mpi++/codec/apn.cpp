
#include "y/mpi++/api.hpp"
#include "y/apex/natural.hpp"
#include "y/apex/m/mem-buff.hpp"

namespace Yttrium
{
    template <>
    void MPI::Codec<apn>::Send(MPI          & mpi,
                               const apn    & n,
                               const size_t   target,
                               const int      tag)
    {
        apn::LockedBuffer buff(n);
        const size_t      sz = buff.length();
        mpi.sendCount(sz,target,tag);
        if(sz>0)
        {
            mpi.sendBlock(buff.ro(),sz,target,tag);
        }
    }

    template <>
    apn MPI::Codec<apn>::Recv(MPI &mpi, const size_t source, const int tag)
    {
        const size_t sz = mpi.recvCount(source,tag,"apn.bytes");
        if(sz<=0)
            return apn();
        else
        {
            Apex::MemBuff buff(sz);
            mpi.recvBlock(buff.rw(),sz,source,tag);
            return apn(buff.ro(),sz,"apn.content");
        }
    }

    


}
