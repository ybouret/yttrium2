#include "y/mpi++/api.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include <cstring>
#include "y/format/hexadecimal.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/mkl/complex.hpp"
#include "y/apex/rational.hpp"

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

#define SHOW_PLAIN(TYPE) \
Y_SIZEOF(TYPE); \
std::cerr << #TYPE << " => plain=" << MPI::Plain<TYPE>::Used  << " | DIMS=" << MPI::Plain<TYPE>::DIMS << std::endl;\
std::cerr << std::endl

Y_UTEST(p2p)
{
    MPI & mpi = MPI::Init(&argc,&argv);
    if(mpi.primary) std::cerr << "using " << mpi.callSign() << std::endl;


    Y_MPI_ForEach(mpi,std::cerr << "foreach @" << mpi <<std::endl);

    TestP2P<int>(mpi);
    TestP2P<uint16_t>(mpi);
    TestP2P<float>(mpi);

    long int       idx = 0;
    String         str;
    Complex<float> cpx;
    apn            nnn;
    apz            zzz;
    apq            qqq;

    if(mpi.primary)
    {
        idx = 7;
        str = "Hello, World!";
        cpx.re = 1.2;
        cpx.im = -0.3;
        nnn    = 101;
        zzz    = -42;
        qqq    = Fraction { 2, 3 };

        for(size_t rank=1;rank<mpi.size;++rank)
        {
            mpi.send1(idx,rank);
            mpi.send1(str,rank);
            mpi.send1(cpx,rank);
            mpi.send1(nnn,rank);
            mpi.send1(zzz,rank);
            mpi.send1(qqq,rank);
        }
    }
    else
    {
        if(mpi.parallel) {
            mpi.load1(idx,0);
            mpi.load1(str,0);
            mpi.load1(cpx,0);
            mpi.load1(nnn,0);
            mpi.load1(zzz,0);
            mpi.load1(qqq,0);
        }
    }

    Y_MPI_ForEach(mpi,std::cerr << "index   @" << mpi << " : " << idx << std::endl);
    Y_MPI_ForEach(mpi,std::cerr << "string  @" << mpi << " : " << str << std::endl);
    Y_MPI_ForEach(mpi,std::cerr << "complex @" << mpi << " : " << cpx << std::endl);
    Y_MPI_ForEach(mpi,std::cerr << "apn     @" << mpi << " : " << nnn << std::endl);
    Y_MPI_ForEach(mpi,std::cerr << "apz     @" << mpi << " : " << zzz << std::endl);
    Y_MPI_ForEach(mpi,std::cerr << "apq     @" << mpi << " : " << qqq << std::endl);


    if(mpi.primary)
    {
        SHOW_PLAIN(char);
        SHOW_PLAIN(String);
        SHOW_PLAIN(Complex<float>);
    }


}
Y_UDONE()

