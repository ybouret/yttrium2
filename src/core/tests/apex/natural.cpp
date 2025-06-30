
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;



Y_UTEST(apex_n)
{
    Random::ParkMiller ran;

    {
        Apex::Natural n;
        std::cerr << n << std::endl;
    }

    {
        Apex::Natural n = 0x234;
        std::cerr << n << std::endl;
        n = 0xabcde;
        std::cerr << n << std::endl;
    }

    for(size_t p=0;p<=80;++p)
    {
        Apex::Natural n(TwoToThePowerOf,p);
        std::cerr << n << std::endl;
    }

    for(size_t p=0;p<=80;++p)
    {
        for(size_t i=0;i<4;++i)
        {
            Apex::Natural n(ran,p);
            std::cerr << n << std::endl;
        }
    }

}
Y_UDONE()
