


#include "y/protean/coop/heavy/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(protean_coop_heavy_list)
{
    System::Rand ran;

    typedef Protean::CoopHeavyList<int,SingleThreadedClass> STList;
    typedef STList::PoolType STPool;

    STPool st_pool;

    Protean::CoopHeavyList<int,SingleThreadedClass> st_list(st_pool);
    

}
Y_UDONE()
