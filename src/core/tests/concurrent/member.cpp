
#include "y/concurrent/member.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;
using namespace Concurrent;

Y_UTEST(concurrent_member)
{
    Random::ParkMiller ran;

    for(size_t size=1;size<=1024; size <<= 1)
    {
        std::cerr << std::endl;
        for(size_t i=0;i<10;++i)
        {
            const Concurrent::Member m(size, ran.lt<size_t>(size) );
            std::cerr << m.name() << std::endl;
        }
    }

}
Y_UDONE()
