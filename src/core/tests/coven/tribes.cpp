
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

    const double  proba_z   = 0.2;
    const double  proba_dup = 0.3;
    Coven::Survey survey;

    for(size_t dims=1;dims<=5;++dims)
    {
        std::cerr << std::endl;
        std::cerr << "-------- dimensions = " << dims << std::endl;
        Coven::QVector::Pool vp(dims);
        Coven::QFamily::Pool fp(vp);

        for(size_t n=1;n<=dims;++n)
        {
            std::cerr << "---------------- n=" << n << std::endl;
            Matrix<int> mu(n,dims);
            {
                for(size_t i=1;i<=n;++i)
                {
                    Writable<int> &a = mu[i];
                    for(size_t j=dims;j>0;--j) a[j] = ran.in<int>(-5,5);
                }

                if( ran.to<double>() < proba_z)   mu[ ran.in<size_t>(1,n) ].ld(0);
                if( ran.to<double>() < proba_dup) mu[ ran.in<size_t>(1,n) ].ld( mu[ ran.in<size_t>(1,n) ] );

                survey.list.release();

                Coven::Tribes tribes(mu,ip,fp,&survey);
                size_t count = tribes.size;
                while(tribes.size>0)
                {
                    count += tribes.generate(mu,&survey);
                }
                const apn mx = MaxTribes(n);
                std::cerr << "count = " << count << "/" << mx << std::endl;
                Y_ASSERT(mx>=count);

            }


        }
    }


    for(size_t n=1;n<=10;++n)
    {
        std::cerr << "MaxTribes(" << n << ")=" << MaxTribes(n) << std::endl;
    }

    Y_SIZEOF(Coven::Tribe);
}
Y_UDONE()
