
#include "y/mpi++/api.hpp"

namespace Yttrium
{

    template <>
    void MPI::Codec<String>::Send(MPI          & mpi,
                                  const String & str,
                                  const size_t   target,
                                  const int      tag)
    {
        const size_t sz = str.size();
        mpi.sendCount(sz,target,tag);
        if(sz>0)
        {
            mpi.sendBlock(str.c_str(),sz,target,tag);
        }
    }

    template <>
    String MPI::Codec<String>::Recv(MPI &mpi, const size_t source, const int tag)
    {
        const size_t sz = mpi.recvCount(source,tag,"string.size");
        String s(WithAtLeast,sz,true);
        if(sz>0)
        {
            mpi.recvBlock( &s[1], sz, source, tag);
        }
        return s;
    }

}
