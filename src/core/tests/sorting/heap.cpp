
#include "y/sorting/heap.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/core/display.hpp"

namespace Yttrium
{



}


using namespace Yttrium;

Y_UTEST(sorting_heap)
{

    System::Rand ran;
    int          arr[10] = {};
    const size_t num = sizeof(arr)/sizeof(arr[0]);

    for(size_t i=0;i<num;++i)
    {
        arr[i] = int(i);
    }
    ran.shuffle(arr,num);
    Core::Display(std::cerr,arr,num) << std::endl;
    Sorting::Heap::Sort(arr,num,Sign::Increasing<int>);
    Core::Display(std::cerr,arr,num) << std::endl;

}
Y_UDONE()
