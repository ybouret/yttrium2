
#include "y/container/sequence/vector.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(sequence_vector)
{
    Vector<size_t> v;

    std::cerr << v << std::endl;

    for(size_t i=0;i<20;++i)
    {
        v.pushTail(i);
        std::cerr << v << std::endl;
    }

    v.release();
    for(size_t i=0;i<20;++i)
    {
        v.pushHead(i);
        std::cerr << v << std::endl;
    }
    std::cerr << v[1] << std::endl;
    v.free();
    std::cerr << v << std::endl;


}
Y_UDONE()

