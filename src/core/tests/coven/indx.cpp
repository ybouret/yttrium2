
#include "y/apex/api/coven/iset.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(coven_indx)
{

    Coven::IPoolType pool;

    {
        Coven::IList     il(pool);
        il << 7 << 2 << 4 << 7;
        std::cerr << il << std::endl;
    }

    std::cerr << "pool.size=" << pool.count() << std::endl;

    {
        Coven::IList     il(pool);
        Coven::ISet      is(pool);
        il << 1 << 7 << 3 << 10;
        std::cerr << il << std::endl;
        while(il.size()) is << il->popHead();
        std::cerr << is << std::endl;
    }


}
Y_UDONE()

