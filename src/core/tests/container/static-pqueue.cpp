
#include "y/utest/run.hpp"
#include "y/container/ordered/static-priority-queue.hpp"
#include "y/system/rand.hpp"



using namespace Yttrium;

Y_UTEST(ordered_static_pqueue)
{
    System::Rand    ran;

    StaticPriorityQueue< int,8,Sign::DecreasingComparator<int> > pq;

    pq << 1; std::cerr << pq << " @" << pq->peek() << std::endl;
    pq << 4; std::cerr << pq << " @" << pq->peek() << std::endl;
    pq << 2; std::cerr << pq << " @" << pq->peek() << std::endl;
    pq << 3; std::cerr << pq << " @" << pq->peek() << std::endl;


}
Y_UDONE()
