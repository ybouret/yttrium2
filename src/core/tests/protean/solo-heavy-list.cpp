

#include "y/protean/solo/heavy/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/threading/global-multi-threaded.hpp"
#include "y/container/iter/tests.hpp"
#include "y/concurrent/mutex.hpp"

using namespace Yttrium;

Y_UTEST(protean_solo_heavy_list)
{
    System::Rand ran;

    Concurrent::Mutex mutex;
    List<int,SingleThreadedClass> st_list;
    List<int,MultiThreadedObject> mt_list;
    List<int,MultiThreadedHandle> sh_list(mutex);
    List<int,GlobalMultiThreaded> gb_list;


    for(int i=1;i<=13;++i)
    {
        if(ran.choice())
        {
            st_list << i;
            mt_list << i;
            sh_list << i;
            gb_list << i;
        }
        else
        {
            st_list >> i;
            mt_list >> i;
            sh_list >> i;
            gb_list >> i;
        }
    }

    Iter::Test::All(st_list);
    Iter::Test::All(mt_list);
    Iter::Test::All(sh_list);
    Iter::Test::All(gb_list);

    List<int,SingleThreadedClass> st_list2(st_list);
    List<int,MultiThreadedObject> mt_list2(mt_list);
    List<int,MultiThreadedHandle> sh_list2(sh_list);
    List<int,GlobalMultiThreaded> gb_list2(gb_list);

    std::cerr << st_list << "/" << st_list2 << std::endl;
    std::cerr << mt_list << "/" << mt_list2 << std::endl;
    std::cerr << sh_list << "/" << sh_list2 << std::endl;
    std::cerr << gb_list << "/" << gb_list2 << std::endl;

}
Y_UDONE()
