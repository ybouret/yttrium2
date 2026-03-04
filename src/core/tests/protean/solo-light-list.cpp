

#include "y/protean/solo/light/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/threading/global-multi-threaded.hpp"
#include "y/container/iter/tests.hpp"
#include "y/concurrent/mutex.hpp"

using namespace Yttrium;

Y_UTEST(protean_solo_light_list)
{
    System::Rand ran;
    float        array[] = { 1, 2, 3, 4, 5, 6, 7};


    Concurrent::Mutex mutex;
    Protean::SoloLightList<float,SingleThreadedClass> st_list;
    Protean::SoloLightList<float,MultiThreadedObject> mt_list;
    Protean::SoloLightList<float,MultiThreadedHandle> sh_list(mutex);
    Protean::SoloLightList<float,GlobalMultiThreaded> gb_list;

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
            mt_list << array[i];
            st_list << array[i];
            sh_list << array[i];
            gb_list << array[i];
        }
    }

    Iter::Test::All(st_list);

    Protean::SoloLightList<float,SingleThreadedClass> st_list2(st_list);
    Protean::SoloLightList<float,MultiThreadedObject> mt_list2(mt_list);
    Protean::SoloLightList<float,MultiThreadedHandle> sh_list2(sh_list);
    Protean::SoloLightList<float,GlobalMultiThreaded> gb_list2(gb_list);

    std::cerr << st_list << "/" << st_list2 << std::endl;
    std::cerr << mt_list << "/" << mt_list2 << std::endl;
    std::cerr << sh_list << "/" << sh_list2 << std::endl;
    std::cerr << gb_list << "/" << gb_list2 << std::endl;
}
Y_UDONE()
