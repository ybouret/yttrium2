#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include <cstring>
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

template <typename T, const size_t N>
static inline void TestP2P(MPI &mpi)
{
    Random::ParkMiller ran;

    int original[N];
    memset(original,0,sizeof(original));
    if(mpi.primary)
    {
        for(size_t i=0;i<N;++i) original[i] = ran.to<T>();
        Hexadecimal::Display(std::cerr << "original=",original,N) << std::endl;
        for(size_t k=1;k<mpi.size;++k)
        {
            mpi.send(original,N,k);
        }

    }
    else
    {
        if(mpi.parallel)
        {
            mpi.recv(original,N,0);
        }
        
    }


}

Y_UTEST(p2p)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    if(mpi.primary) std::cerr << "using " << mpi.callSign() << std::endl;
    TestP2P<int,10>(mpi);


}
Y_UDONE()

