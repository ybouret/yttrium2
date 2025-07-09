
#include "y/apex/integer.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;



Y_UTEST(apex_z)
{
    Random::ParkMiller ran;

    {
        apz z;
        std::cerr << z << std::endl;
    }

    {
        const Apex::integer_t arr[3] = { -5, 0, 3 };
        const size_t          num    = sizeof(arr)/sizeof(arr[0]);

        for(size_t i=0;i<num;++i)
        {
            const int64_t u = arr[i];
            const apz     U = u;
            for(size_t j=0;j<num;++j)
            {
                const int64_t v = arr[j];
                const apz     V = v;


                const int64_t s = u + v;
                const apz     S = apz::Add(U,V);
                Y_ASSERT(s==S);
                //std::cerr << U << " + " << V << " => " << S << std::endl;
                std::cerr << "Add(" << U << "," << v << ")=" << apz::Add(U,v) << std::endl;
                Y_ASSERT(apz::Add(U,v)==S);
                Y_ASSERT(apz::Add(u,V)==S);

            }
        }

    }

#if 0
    {
        apz z = 10;
        z    += 10;
        std::cerr << z << std::endl;
        z    -= 10;
        std::cerr << z << std::endl;
    }

    for(apz i=-5;i<=5;)
    {
        std::cerr << ' ' << ++i;
    }
    std::cerr << std::endl;

    for(apz i=-5;i<=5;)
    {
        std::cerr << ' ' << i++;
    }
    std::cerr << std::endl;



    for(apz i=5;i>=-5;)
    {
        std::cerr << ' ' << --i;
    }
    std::cerr << std::endl;

    for(apz i=5;i>=-5;)
    {
        std::cerr << ' ' << i--;
    }
    std::cerr << std::endl;

#endif
    
}
Y_UDONE()
