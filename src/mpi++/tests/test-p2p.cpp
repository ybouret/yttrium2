#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include <cstring>
#include "y/format/hexadecimal.hpp"
#include "y/container/sequence/vector.hpp"


using namespace Yttrium;




template <typename T>
static inline void TestP2P(MPI &mpi)
{
    Random::ParkMiller ran;
    const T            zero = 0;
    size_t             num  = 0;
    Vector<T>          arr;

    if(mpi.primary)
    {
        num = ran.in<size_t>(1,10);
        std::cerr << "@primary " << mpi << " : " << num << std::endl;
        if(mpi.parallel)
        {
            for(size_t rank=1;rank<mpi.size;++rank)
            {
                mpi.sendCount(num,rank,MPI::DefaultTag);
                mpi.syn(rank);
            }
        }
    }
    else
    {
        if(mpi.parallel)
        {
            num = mpi.recvCount(0,MPI::DefaultTag,"num");
            std::cerr << "@replica " << mpi << " : " << num << std::endl;
            mpi.ack(0);
        }
    }

    arr.adjust(num,zero);
    if(mpi.primary)
    {
        for(size_t i=num;i>0;--i)
        {
            arr[i] = ran.to<T>();
        }
        std::cerr << "@" << mpi << " : " << arr << std::endl;
        if(mpi.parallel)
        {
            for(size_t rank=1;rank<mpi.size;++rank)
            {
                mpi.send(&arr[1],num,rank);
                mpi.syn(rank);
            }
        }

    }
    else
    {
        if(mpi.parallel)
        {
            mpi.recv(&arr[1],num,0);
            std::cerr << "@" << mpi << " : " << arr << std::endl;
            mpi.ack(0);
        }
    }



}

#define SHOW_PLAIN(TYPE) std::cerr << #TYPE << " => plain=" << MPI::Plain<TYPE>::Used << std::endl

Y_UTEST(p2p)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    if(mpi.primary) std::cerr << "using " << mpi.callSign() << std::endl;


    Y_MPI_ForEach(mpi,std::cerr << "foreach @" << mpi <<std::endl);

    TestP2P<int>(mpi);
    TestP2P<uint16_t>(mpi);
    TestP2P<float>(mpi);

    String str;
    if(mpi.primary)
    {
        str = "Hello, World!";
        for(size_t rank=1;rank<mpi.size;++rank)
        {
            //mpi.sendString(str,rank);
            mpi.send1(str,rank);
        }
    }
    else
    {
        if(mpi.parallel) {
            //str = mpi.recvString(0);
            str = mpi.recv1<String>(0);
        }
    }

    Y_MPI_ForEach(mpi,std::cerr << "string @" << mpi << " : " << str << std::endl);

    if(mpi.primary)
    {
        SHOW_PLAIN(char);
        SHOW_PLAIN(String);
        
    }


}
Y_UDONE()

