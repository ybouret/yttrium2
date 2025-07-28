
#include "y/apex/api/coven/tribes.hpp"
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    static inline apn MaxTribes(const size_t n)
    {

        apn sum = 0;
        for(size_t k=1;k<=n;++k)
        {
            sum += apn::Enum(n,k);
        }
        return sum;
    }
}

Y_UTEST(coven_tribes)
{

    Coven::IPool        idxPool;
    Coven::Tribe::Cache trCache;

    for(size_t n=1;n<=4;++n)
    {
        std::cerr << std::endl;
        std::cerr << "--- dimensions=" << n << std::endl;
        std::cerr << "root generation:" << std::endl;
        size_t count = 0;
        Coven::Tribes tribes(idxPool,trCache,n);
        count += tribes.size;
        std::cerr << "next generation" << std::endl;
        while(tribes.generate()>0)
        {
            count += tribes.size;
        }
        const apn mx = MaxTribes(n);
        std::cerr << "done " << count << " / " << mx << std::endl;
        Y_ASSERT(count == mx);
    }


    for(size_t n=1;n<=10;++n)
    {
        std::cerr << "MaxTribes(" << n << ")=" << MaxTribes(n) << std::endl;
    }


}
Y_UDONE()
