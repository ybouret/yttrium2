#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_rand)
{
    System::Rand ran;
    for(size_t i=0;i<10;++i)
    {
        std::cerr << ran.to<float>() << " " << ran.to<double>() << " " << ran.to<long double>() << std::endl;
    }
}
Y_UDONE()


