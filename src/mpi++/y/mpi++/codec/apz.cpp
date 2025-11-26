

#include "y/mpi++/api.hpp"
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace
    {
        typedef int  SignT;
        static const SignT IsNegative = -1;
        static const SignT Is__Zero__ =  0;
        static const SignT IsPositive =  1;
    }

    template <>
    void MPI::Codec<apz>::Send(MPI          & mpi,
                               const apz    & z,
                               const size_t   target,
                               const int      tag)
    {

        // send sign
        switch(z.s)
        {
            case __Zero__: mpi.send1(Is__Zero__,target,tag); return;
            case Positive: mpi.send1(IsPositive,target,tag); break;
            case Negative: mpi.send1(IsNegative,target,tag); break;
        }

        
        // send non-zero integer
        mpi.send1(z.n,target,tag);
    }

    template <>
    apz MPI::Codec<apz>::Recv(MPI &mpi, const size_t source, const int tag)
    {

        // recv sign
        SignType    s  = __Zero__;

        {
            const SignT st = mpi.recv1<SignT>(source,tag);
            switch(st)
            {
                case Is__Zero__: return apz();
                case IsPositive: s = Positive; break;
                case IsNegative: s = Negative; break;
                default:
                    throw Specific::Exception("MPI::Revc<apz>", "bad sign");
            }
        }

        assert(__Zero__!=s);
        const apn n = mpi.recv1<apn>(source,tag);
        return apz(s,n);
    }




}
