#include "y/utest/run.hpp"
#include "y/container/ordered/priority-queue.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/random/park-miller.hpp"
#include "y/apex/integer.hpp"


using namespace Yttrium;

Y_UTEST(ordered_pqueue)
{
    Random::ParkMiller ran;
    {
        void *          wksp[ 10 ];
        const size_t    wlen = sizeof(wksp);
        const size_t    numBlocks = wlen / sizeof(int);
        PrioQueue<unsigned> pq(Memory::Stealth::Cast<unsigned>(Y_Memory_BZero(wksp)), numBlocks);

        for(size_t i=0;i<pq.capacity;++i)
        {
            pq.push( ran.to<unsigned>( ran.leq<size_t>(10) ), Sign::Decreasing<unsigned> ); std::cerr << pq << std::endl;
        }

        Vector<unsigned> vec;
        while(pq.size) vec << pq.pop( Sign::Decreasing<unsigned> );
        std::cerr << vec << std::endl;
    }

    PriorityQueue<apz> pq;
    std::cerr << pq << std::endl;
    for(size_t i=0;i<20;++i)
    {
        pq << apz(ran,10);
        std::cerr << pq << std::endl;
    }
    
}
Y_UDONE()
