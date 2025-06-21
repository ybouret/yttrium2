

#include "y/protean/solo/light/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(protean_solo_light_list)
{
    System::Rand ran;
    float        array[] = { 1, 2, 3, 4 };

    Protean::SoloLightList<float,SingleThreadedClass> st_list;
    Protean::SoloLightList<float,MultiThreadedObject> mt_list;

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

    Protean::SoloLightList<float,SingleThreadedClass> st_list2(st_list);
    Protean::SoloLightList<float,MultiThreadedObject> mt_list2(mt_list);

}
Y_UDONE()
