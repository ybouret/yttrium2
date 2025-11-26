
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


    void MPI:: sendrecv(const void * const sendEntry,
                        const size_t       sendCount,
                        const MPI_Datatype sendDatatype,
                        const uint64_t     sendBytes,
                        const size_t       sendTarget,
                        const int          sendTag,
                        void * const       recvEntry,
                        const size_t       recvCount,
                        const MPI_Datatype recvDatatype,
                        const uint64_t     recvBytes,
                        const size_t       recvSource,
                        const int          recvTag)
    {
        static const char fn[] = "MPI::sendrecv";
        assert( Good(sendEntry,sendCount) );
        assert( Good(recvEntry,recvCount) );
        assert(recvSource<size);
        assert(recvSource!=rank);
        assert(sendTarget<size);
        assert(sendTarget!=rank);

        MPI_Status     status;
        Y_MPI_Mark();
        Y_MPI_Call( MPI_Sendrecv(sendEntry,GetCount(sendCount,fn),sendDatatype, (int) sendTarget, sendTag,
                                 recvEntry,GetCount(recvCount,fn),recvDatatype, (int) recvSource, recvTag,
                                 MPI_COMM_WORLD,
                                 &status));
        {
            const uint64_t delta = Y_MPI_Gain();
            recvRate.ticks += delta;
            sendRate.ticks += delta;
        }
        sendRate.bytes += sendBytes;
        recvRate.bytes += recvBytes;
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
                           const int          tag,
                           const char * const varName)
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

    void MPI:: syn(const size_t source)
    {
        char c = 0;
        recv(&c,1,source);
        if(SYMB!=c) throw Specific::Exception("MPI::syn","corrupted");
    }

    void MPI:: ack(const size_t target)
    {
        send(&SYMB,1,target);
    }

    void MPI:: syncWith(const size_t target)
    {
        ack(target);
        syn(target);
    }




}

