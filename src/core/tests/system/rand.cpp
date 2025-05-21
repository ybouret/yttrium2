#include "y/core/display.hpp"
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

    for(size_t i=0;i<10;++i)
    {
        std::cerr << ran.leq(8) << ' ';
    }
    std::cerr << std::endl;

    unsigned       array[10];
    const unsigned length =sizeof(array)/sizeof(array[0]);
    for(unsigned i=0;i<length;++i) array[i] = i+1;

    Core::Display(std::cerr,array,length) << std::endl;
    ran.shuffle(array,length);
    Core::Display(std::cerr,array,length) << std::endl;
    ran.shuffle(array,length);
    Core::Display(std::cerr,array,length) << std::endl;

}
Y_UDONE()


