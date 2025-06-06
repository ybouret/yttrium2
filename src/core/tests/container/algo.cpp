#include "y/container/algorithm/reverse.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(container_algo)
{
    static const unsigned n=7;
    unsigned array[n] = { 0 };
    Y_Memory_BZero(array);

    for(unsigned m=0;m<=n;++m)
    {
        std::cerr << "reverse " << m << std::endl;
        for(unsigned i=0;i<n;++i) array[i]=i;
        Core::Display(std::cerr,array,n) << std::endl;
        Algorithm::Reverse(array,m,Swap<unsigned>);
        Core::Display(std::cerr,array,n) << std::endl;
        Algorithm::Reverse(array,m,Memory::Stealth::Swap<unsigned>);
        Core::Display(std::cerr,array,n) << std::endl;
        std::cerr << std::endl;
        for(unsigned i=0;i<n;++i)
        {
            Y_ASSERT(array[i]==i);
        }

    }

}
Y_UDONE()

