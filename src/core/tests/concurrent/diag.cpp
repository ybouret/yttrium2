

#include "y/concurrent/divide/udts.hpp"
#include "y/utest/run.hpp"
#include "y/string/env/convert.hpp"

#include "y/calculus/alignment.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;




Y_UTEST(concurrent_diag)
{

    const size_t nmin = EnvironmentConvert::To<size_t>("nmin",1);
    const size_t nmax = EnvironmentConvert::To<size_t>("nmax",10);
    const size_t cpus = 8;

    for(size_t n=nmin;n<=nmax;++n)
    {
        std::cerr << "n=" << n << std::endl;

        {
            Concurrent::Divide::UpperDiagonalTile udt(1,0,n);
            size_t k = 0;
            for(size_t i=1;i<=n;++i)
            {
                for(size_t j=i;j<=n;++j)
                {
                    ++k; Y_ASSERT(k<=udt.kNumber);
                    const MatrixCoord p = udt(k);
                    Y_ASSERT(p.r == i);
                    Y_ASSERT(p.c == j);
                }
            }

        }

        for(size_t cpu=1;cpu<=cpus;++cpu)
        {
            std::cerr << "#cpu = " << cpu << std::endl;
            Concurrent::Divide::UpperDiagonalTiles udts(cpu,n);

        }

    }



    

}
Y_UDONE()
