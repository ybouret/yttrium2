
#include "y/apex/api/coven/tribes.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(coven_tribes)
{

    Coven::IPool        idxPool;
    Coven::Tribe::Cache trCache;

    for(size_t n=1;n<=3;++n)
    {
        std::cerr << std::endl;
        std::cerr << "--- dimensions=" << n << std::endl;
        Coven::Tribes tribes(idxPool,trCache,n);

    }

}
Y_UDONE()
