
#include "y/apex/api/coven/iset.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(coven_indx)
{

    Coven::IPoolType pool;

    {
        Coven::IList     il(pool);
        il << 1 << 2 << 4 << 7;
        std::cerr << il << std::endl;
    }

    std::cerr << "pool.size=" << pool.count() << std::endl;

}
Y_UDONE()

