

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
    

}
Y_UDONE()
