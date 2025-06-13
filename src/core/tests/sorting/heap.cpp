
#include "y/sorting/heap.hpp"
#include "y/sorting/test.hpp"
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
    static const size_t num = sizeof(arr)/sizeof(arr[0]);
    long double  brr[10] = {};

    for(size_t i=0;i<num;++i)
    {
        arr[i] = int(i);
        brr[i] = float(i);
    }
    std::cerr << "v1" << std::endl;
    ran.shuffle(arr,num);
    Core::Display(std::cerr << "a=",arr,num) << std::endl;
    Sorting::Heap::Sort(arr,num,Sign::Increasing<int>);
    Core::Display(std::cerr << "a=",arr,num) << std::endl;
    Y_CHECK(Sorting::Test::AccordingTo(Sign::Increasing<int>,arr,num));
    std::cerr << std::endl;

    std::cerr << "v2" << std::endl;
    ran.shuffle(arr,num);
    Core::Display(std::cerr << "a=",arr,num) << std::endl;
    Core::Display(std::cerr << "b=",brr,num) << std::endl;
    Sorting::Heap::Sort(arr,brr,num,Sign::Increasing<int>);
    Core::Display(std::cerr << "a=",arr,num) << std::endl;
    Core::Display(std::cerr << "b=",brr,num) << std::endl;
    Y_CHECK(Sorting::Test::AccordingTo(Sign::Increasing<int>,arr,num));

}
Y_UDONE()
