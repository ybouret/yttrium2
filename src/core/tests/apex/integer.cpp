
#include "y/apex/integer.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;



Y_UTEST(apex_z)
{
    Random::ParkMiller ran;

    {
        std::cerr << "Default..." << std::endl;
        apz z;
        std::cerr << z << std::endl;
    }

    {
        std::cerr << "Add/Sub cases..." << std::endl;
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
                const int64_t d = u-v;
                const apz     S = apz::Add(U,V);
                const apz     D = apz::Sub(U,V);

                Y_ASSERT(s==S);
                Y_ASSERT(d==D);
                Y_ASSERT(apz::Add(U,v)==S);
                Y_ASSERT(apz::Add(u,V)==S);

                Y_ASSERT(apz::Sub(U,v)==D);
                Y_ASSERT(apz::Sub(u,V)==D);


                if(u>=0)
                {
                    const apn nu = u;
                    Y_ASSERT(apz::Add(nu,V)==S);
                    Y_ASSERT(apz::Sub(nu,V)==D);
                }

                if(v>=0)
                {
                    const apn nv = v;
                    Y_ASSERT(apz::Add(U,nv)==S);
                    Y_ASSERT(apz::Sub(U,nv)==D);
                }

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
