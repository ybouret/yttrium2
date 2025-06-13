

#include "y/sorting/index.hpp"
#include "y/sorting/test.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/core/display.hpp"
#include "y/container/sequence/vector.hpp"



using namespace Yttrium;

Y_UTEST(sorting_index)
{

    System::Rand ran;

    const size_t   num = 10;
    Vector<size_t> idx(num,0);
    Vector<float>  arr(WithAtLeast,num);
    for(size_t i=num;i>0;--i)
    {
        arr.pushTail( ran.to<float>() );
    }
    Y_ASSERT(idx.size()==arr.size());

    Sorting::Index::Make(idx, Sign::Increasing<float>, arr);
    std::cerr << "idx=" << idx << std::endl;
    std::cerr << "arr=" << arr << std::endl;
    for(size_t i=1;i<=num;++i)
        std::cerr << "\t" << arr[ idx[i] ] << std::endl;


}
Y_UDONE()
