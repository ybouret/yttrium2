

#include "y/protean/solo/heavy/list.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/container/iter/tests.hpp"

using namespace Yttrium;

Y_UTEST(protean_solo_heavy_list)
{
    System::Rand ran;

    Protean::SoloHeavyList<int,SingleThreadedClass> st_list;
    Protean::SoloHeavyList<int,MultiThreadedObject> mt_list;


    for(int i=1;i<=6;++i)
    {
        if(ran.choice())
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
    Iter::Test::All(mt_list);


}
Y_UDONE()
