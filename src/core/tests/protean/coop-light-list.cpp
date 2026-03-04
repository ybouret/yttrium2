


#include "y/protean/coop/light/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/threading/global-multi-threaded.hpp"
#include "y/container/iter/tests.hpp"
#include "y/concurrent/mutex.hpp"

using namespace Yttrium;

Y_UTEST(protean_coop_light_list)
{
    System::Rand ran;
    double       array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    Concurrent::Mutex mutex;
    typedef Protean::CoopLightList<double,SingleThreadedClass> STList;
    typedef Protean::CoopLightList<double,MultiThreadedObject> MTList;
    typedef Protean::CoopLightList<double,MultiThreadedHandle> SHList;
    typedef Protean::CoopLightList<double,GlobalMultiThreaded> GBList;


    STList::PoolType st_pool;
    MTList::PoolType mt_pool;
    SHList::PoolType sh_pool(mutex);
    GBList::PoolType gb_pool;

    {
        STList           st_list(st_pool);
        MTList           mt_list(mt_pool);
        SHList           sh_list(sh_pool,mutex);
        GBList           gb_list(gb_pool);


        for(size_t i=0;i<sizeof(array)/sizeof(array[0]);++i)
        {
            if( ran.choice() ) {
                st_list >> array[i];
                mt_list >> array[i];
                sh_list >> array[i];
                gb_list >> array[i];
            }
            else
            {
                st_list << array[i];
                mt_list << array[i];
                sh_list << array[i];
                gb_list << array[i];
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
