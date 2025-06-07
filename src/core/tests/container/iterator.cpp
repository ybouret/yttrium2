
#include "y/container/iterator/linear.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(container_iterator)
{

    int array[10];

    const size_t n = sizeof(array)/sizeof(array[0]);
    for(size_t i=0;i<n;++i) array[i] = int(i);

    Iterator::Linear<Iterator::Forward,int>       lhs = array;
    const Iterator::Linear<Iterator::Forward,int> end = array+n;

    for(;lhs!=end;++lhs)
    {
        std::cerr << *lhs << std::endl;
    }
}
Y_UDONE()
