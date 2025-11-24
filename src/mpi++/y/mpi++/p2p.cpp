
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
        Y_MPI_Mark();
        Y_MPI_Call( MPI_Send(entry, GetCount(count,"MPI::send"), datatype, (int)dest, tag, MPI_COMM_WORLD) );
        sendRate.ticks += Y_MPI_Gain();
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
        Y_MPI_Mark();
        MPI_Status     status;
        Y_MPI_Call( MPI_Recv(entry, GetCount(count,"MPI::recv"), datatype, (int)source, tag, MPI_COMM_WORLD, &status) );
        recvRate.ticks += Y_MPI_Gain();
        recvRate.bytes += bytes;
    }


    void MPI:: recvBlock(void * const entry,
                         const size_t count,
                         const size_t source,
                         const int    tag)
    {
        recv(entry,count,MPI_BYTE,count,source,tag);
    }


    void MPI:: sendCount(const size_t value,
                         const size_t dest,
                         const int    tag)
    {
        const uint64_t qw = value;
        send(&qw,1,dest,tag);
    }

    size_t MPI:: recvCount(const size_t       source,
                           const char * const varName,
                           const int          tag)
    {
        static const uint64_t MaxQW = IntegerFor<size_t>::Maximum;
        uint64_t qw = 0;

        recv(&qw,1,source,tag);
        if(qw>MaxQW) {
            Specific::Exception excp("MPI::recvCount","overflow");
            if(varName) excp.add(" for '%s'",varName);
            throw excp;
        }

        return (size_t)qw;

    }

    static const char SYMB = 'Y';

    void MPI:: syn(const size_t target)
    {
        char c = 0;
        recv(&c,1,target);
        if(SYMB!=c) throw Specific::Exception("MPI::syn","corrupted");
    }

    void MPI:: ack(const size_t source)
    {
        send(&SYMB,1,source);
    }
}

