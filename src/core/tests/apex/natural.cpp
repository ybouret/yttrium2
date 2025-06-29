
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;



Y_UTEST(apex_n)
{
    System::Rand ran;

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

}
Y_UDONE()
