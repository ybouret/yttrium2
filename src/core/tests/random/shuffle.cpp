

#include "y/random/shuffle.hpp"

#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"
#include "y/core/display.hpp"
#include "y/sorting/heap.hpp"
#include <cstring>

using namespace Yttrium;


namespace {



}


Y_UTEST(random_shuffle)
{
    Random::ParkMiller ran;

    static const size_t num = 22;
    size_t              org[num];
    size_t              arr[num];
    for(size_t i=0;i<num;++i) org[i] = arr[i] = i;

    Core::Display(std::cerr,arr,num) << std::endl;

    for(int iter=0;iter<8;++iter)
    {
        Random::Shuffle::Range(ran,arr,num);
        Core::Display(std::cerr,arr,num) << std::endl;
        Sorting::Heap::Sort(arr,num,Sign::Increasing<size_t>);
        Core::Display(std::cerr,arr,num) << std::endl;
        Y_CHECK( 0 == memcmp(org,arr,sizeof(org)) );
    }
}
Y_UDONE()
