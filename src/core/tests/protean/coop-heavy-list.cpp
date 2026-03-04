


#include "y/protean/coop/heavy/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/threading/global-multi-threaded.hpp"
#include "y/container/iter/tests.hpp"
#include "y/concurrent/mutex.hpp"

using namespace Yttrium;

Y_UTEST(protean_coop_heavy_list)
{
    System::Rand ran;

    Concurrent::Mutex mutex;
    typedef Protean::CoopHeavyList<int,SingleThreadedClass> STList;
    typedef Protean::CoopHeavyList<int,MultiThreadedObject> MTList;
    typedef Protean::CoopHeavyList<int,MultiThreadedHandle> SHList;
    typedef Protean::CoopHeavyList<int,GlobalMultiThreaded> GBList;



    STList::PoolType st_pool;
    MTList::PoolType mt_pool;
    SHList::PoolType sh_pool(mutex);
    GBList::PoolType gb_pool;


    {
        STList           st_list(st_pool);
        MTList           mt_list(mt_pool);
        SHList           sh_list(sh_pool,mutex);
        GBList           gb_list(gb_pool);


        for(int i=1;i<=11;++i)
        {
            if( ran.choice() ) {
                st_list >> i;
                mt_list >> i;
                sh_list >> i;
                gb_list >> i;
            }
            else
            {
                st_list << i;
                mt_list << i;
                sh_list << i;
                gb_list << i;
            }
        }

        Iter::Test::All(st_list);
        Iter::Test::All(mt_list);
        Iter::Test::All(sh_list);
        Iter::Test::All(gb_list);

        STList           st_list2(st_list);
        MTList           mt_list2(mt_list);
        SHList           sh_list2(sh_list);
        GBList           gb_list2(gb_list);

        std::cerr << st_list << "/" << st_list2 << std::endl;
        std::cerr << mt_list << "/" << mt_list2 << std::endl;
        std::cerr << sh_list << "/" << sh_list2 << std::endl;
        std::cerr << gb_list << "/" << gb_list2 << std::endl;

    }

    std::cerr << "pool.count=" << st_pool.count() << std::endl;
    std::cerr << "pool.count=" << mt_pool.count() << std::endl;
    std::cerr << "pool.count=" << sh_pool.count() << std::endl;
    std::cerr << "pool.count=" << gb_pool.count() << std::endl;




}
Y_UDONE()
