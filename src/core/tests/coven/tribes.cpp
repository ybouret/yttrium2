
#include "y/apex/api/coven/tribes.hpp"
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/container/matrix.hpp"
#include "../main.hpp"

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

    Random::MT19937     ran;
    Coven::IPool        ip;
    Coven::Tribe::Cache tc;

    const double proba_z = 0.2;

    for(size_t dims=1;dims<=3;++dims)
    {
        std::cerr << std::endl;
        std::cerr << "-------- dimensions = " << dims << std::endl;
        Coven::Carrier cr(dims);
        for(size_t n=1;n<=dims;++n)
        {
            std::cerr << "---------------- n=" << n << std::endl;
            Matrix<int> mu(n,dims);
            Coven::Tribe::Context< Matrix<int> > ctx = { mu, ip, tc, cr };

            {
                for(size_t i=1;i<=n;++i)
                {
                    Writable<int> &a = mu[i];
                    for(size_t j=dims;j>0;--j) a[j] = ran.in<int>(-5,5);
                }

                if( ran.to<double>() < proba_z) mu[ ran.in<size_t>(1,n) ].ld(0);

                Coven::Tribes tribes(ctx);
            }


        }
    }




    for(size_t n=1;n<=10;++n)
    {
        std::cerr << "MaxTribes(" << n << ")=" << MaxTribes(n) << std::endl;
    }


}
Y_UDONE()
