


#include "y/protean/coop/light/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(protean_coop_light_list)
{
    System::Rand ran;
    double       array[] = { 1, 2, 3, 4, 5, 7, 8 };

    typedef Protean::CoopLightList<double,SingleThreadedClass> STList;
    typedef Protean::CoopLightList<double,MultiThreadedObject> MTList;

    STList::PoolType st_pool;
    MTList::PoolType mt_pool;
    STList           st_list(st_pool);
    MTList           mt_list(mt_pool);


    for(size_t i=0;i<sizeof(array)/sizeof(array[0]);++i)
    {
        if( ran.choice() ) {
            st_list >> array[i];
            mt_list >> array[i];
        }
        else
        {
            st_list << array[i];
            mt_list << array[i];
        }
        std::cerr << st_list << std::endl;
        std::cerr << mt_list << std::endl;
    }

    Iter::Test::All(st_list);
    Iter::Test::All(mt_list);

    STList           st_list2(st_list);
    Iter::Test::All(st_list2);

}
Y_UDONE()
