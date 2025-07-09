
#include "y/apex/integer.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;



Y_UTEST(apex_z)
{
    Random::ParkMiller ran;

    {
        apz z;
        std::cerr << z << std::endl;
    }

    {
        apz l = -2;
        apz r =  5;
        
    }

#if 0
    {
        apz z = 10;
        z    += 10;
        std::cerr << z << std::endl;
        z    -= 10;
        std::cerr << z << std::endl;
    }

    for(apz i=-5;i<=5;)
    {
        std::cerr << ' ' << ++i;
    }
    std::cerr << std::endl;

    for(apz i=-5;i<=5;)
    {
        std::cerr << ' ' << i++;
    }
    std::cerr << std::endl;



    for(apz i=5;i>=-5;)
    {
        std::cerr << ' ' << --i;
    }
    std::cerr << std::endl;

    for(apz i=5;i>=-5;)
    {
        std::cerr << ' ' << i--;
    }
    std::cerr << std::endl;

#endif
    
}
Y_UDONE()
