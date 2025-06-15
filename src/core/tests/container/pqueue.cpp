
#include "y/utest/run.hpp"

#include "y/container/ordered/prio-q.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/system/rand.hpp"



using namespace Yttrium;

Y_UTEST(ordered_pqueue)
{
    System::Rand    ran;
    void *          wksp[ 10 ];
    const size_t    wlen = sizeof(wksp);
    const size_t    numBlocks = wlen / sizeof(int);
    PrioQ<unsigned> pq(Memory::Stealth::Cast<unsigned>(Y_Memory_BZero(wksp)), numBlocks);

    for(size_t i=0;i<pq.capacity;++i)
    {
        pq.push( ran.gen<unsigned>( unsigned(ran.leq(10)) ), Sign::Decreasing<unsigned> ); std::cerr << pq << std::endl;
    }

    Vector<unsigned> vec;
    while(pq.size) vec << pq.pop( Sign::Decreasing<unsigned> );
    std::cerr << vec << std::endl;



}
Y_UDONE()
