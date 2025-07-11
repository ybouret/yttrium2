
#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"

using namespace Yttrium;

Y_UTEST(apex_io)
{
    Random::ParkMiller ran;

    Vector<apn> nvec;
    Vector<apz> zvec;

    {
        OutputFile fp("apio.dat");
        size_t nw = 0;
        for(size_t ibits=0;ibits <= 100; ibits += (1+ran.leq(10)))
        {
            const apn n(ran,ibits);
            const apz z(ran,ibits);
            std::cerr << "n=" << n << std::endl;
            std::cerr << "z=" << z << std::endl;
            nw += n.serialize(fp);
            nw += z.serialize(fp);
            nvec << n;
            zvec << z;
        }
        std::cerr << "nw=" << nw << std::endl;
    }

    {
        InputFile fp("apio.dat");
        unsigned i = 1;
        while( fp.alive() )
        {
            {
                const apn n(fp,"apn");
                if(n!=nvec[i]) throw Exception("invalid apn[%u]",i);
            }

            {
                const apz z(fp,"apz");
                if(z!=zvec[i]) throw Exception("invalid apz[%u]",i);
            }
            ++i;
        }
    }
}
Y_UDONE()

