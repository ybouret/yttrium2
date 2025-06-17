
#include "y/protean/bare/light/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"

using namespace Yttrium;

Y_UTEST(protean_bare_light_list)
{
    System::Rand ran;
    float        array[] = { 1, 2, 3, 4 };

    Protean::BareLightList<float,SingleThreadedClass> st_list;
    Protean::BareLightList<float,MultiThreadedObject> mt_list;

    for(size_t i=0;i<sizeof(array)/sizeof(array[0]);++i)
    {
        if( ran.choice() ) {
            st_list >> array[i];
            mt_list >> array[i];
        }
        else
        {
            mt_list << array[i];
            st_list << array[i];
        }
        std::cerr << st_list << std::endl;
        std::cerr << mt_list << std::endl;
    }



}
Y_UDONE()
