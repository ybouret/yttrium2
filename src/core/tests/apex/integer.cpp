
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

}
Y_UDONE()
