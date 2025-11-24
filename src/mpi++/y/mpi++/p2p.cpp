
#include "y/mpi++/api.hpp"
#include "y/system/exception.hpp"
#include "y/type/ints.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{
    void MPI:: send(const void * const entry,
                    const size_t       count,
                    const MPI_Datatype datatype,
                    const uint64_t     bytes,
                    const size_t       dest,
                    const int          tag)
    {
        assert( Good(entry,count) );
        assert(dest<=size);
        assert(dest!=rank);
        const uint64_t mark = System::WallTime::Ticks();
        Y_MPI_Call( MPI_Send(entry, GetCount(count,"MPI::send"), datatype, (int)dest, tag, MPI_COMM_WORLD) );
        sendRate.ticks += System::WallTime::Ticks() - mark;
        sendRate.bytes += bytes;
    }

    void MPI:: sendBlock(const void * const entry,
                         const size_t       count,
                         const size_t       dest,
                         const int          tag)
    {
        send(entry,count,MPI_BYTE,count,dest,tag);
    }


    void MPI:: recv(void * const       entry,
                    const size_t       count,
                    const MPI_Datatype datatype,
                    const uint64_t     bytes,
                    const size_t       source,
                    const int          tag)
    {
        assert( Good(entry,count) );
        assert(source<size);
        assert(source!=rank);
        const uint64_t mark = System::WallTime::Ticks();
        MPI_Status     status;
        Y_MPI_Call( MPI_Recv(entry, GetCount(count,"MPI::recv"), datatype, (int)source, tag, MPI_COMM_WORLD, &status) );
        recvRate.ticks += System::WallTime::Ticks() - mark;
        recvRate.bytes += bytes;
    }


    void MPI:: recvBlock(void * const entry,
                         const size_t count,
                         const size_t source,
                         const int    tag)
    {
        recv(entry,count,MPI_BYTE,count,source,tag);
    }

}

