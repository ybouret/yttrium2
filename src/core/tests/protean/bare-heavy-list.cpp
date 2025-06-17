
#include "y/protean/bare/heavy/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(protean_bare_heavy_list)
{
    System::Rand ran;

    Protean::BareHeavyList<int,SingleThreadedClass> st_list;
    Protean::BareHeavyList<int,MultiThreadedObject> mt_list;

    for(int i=0;i<10;++i)
    {
        if( ran.choice() )
        {
            st_list << i;
            mt_list << i;
        }
        else
        {
            st_list >> i;
            mt_list >> i;
        }
    }


    Iter::Test::All(st_list);


}
Y_UDONE()
