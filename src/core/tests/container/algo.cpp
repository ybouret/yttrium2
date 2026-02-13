#include "y/container/algorithm/flip.hpp"
#include "y/container/algorithm/unique.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;

Y_UTEST(container_algo)
{
    Random::ParkMiller ran;

    {
        static const unsigned n=7;
        unsigned array[n] = { 0 };
        Y_Memory_BZero(array);

        for(unsigned m=0;m<=n;++m)
        {
            std::cerr << "reverse " << m << std::endl;
            for(unsigned i=0;i<n;++i) array[i]=i;
            Core::Display(std::cerr,array,n) << std::endl;
            Algorithm::Flip(array,m,Swap<unsigned>);
            Core::Display(std::cerr,array,n) << std::endl;
            Algorithm::Flip(array,m,Memory::Stealth::Swap<unsigned>);
            Core::Display(std::cerr,array,n) << std::endl;
            std::cerr << std::endl;
            for(unsigned i=0;i<n;++i)
            {
                Y_ASSERT(array[i]==i);
            }

        }
    }

    {
        Vector<unsigned> vec;

        for(size_t i=0;i<10;++i)
            vec << ran.leq<unsigned>(10);

        std::cerr << "vec=" << vec << std::endl;

        (void) Algo::Unique(vec);
        std::cerr << "vec=" << vec << std::endl;


    }

}
Y_UDONE()

