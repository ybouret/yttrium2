
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
                    const int          dest,
                    const int          tag)
    {
        assert( Good(entry,count) );
        const uint64_t mark = System::WallTime::Ticks();
        Y_MPI_Call( MPI_Send(entry, GetCount(count,"MPI::send"), datatype, dest, tag, MPI_COMM_WORLD) );
        sendRate.ticks += System::WallTime::Ticks() - mark;
        sendRate.bytes += bytes;
    }
}

