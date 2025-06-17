

//#include "y/protean/solo/list.hpp"
#include "y/protean/solo/light/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"

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
            st_list.pushHead( array[i] );
            mt_list.pushHead( array[i] );
        }
        else
        {
            st_list.pushTail(array[i]);
            mt_list.pushTail(array[i]);
        }
        std::cerr << st_list << std::endl;
        std::cerr << mt_list << std::endl;
    }



}
Y_UDONE()
