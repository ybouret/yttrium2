
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
        std::cerr << "Ops cases..." << std::endl;
        const Apex::integer_t arr[] = { -9, -7, 0, 3, 17 };
        const size_t          num   = sizeof(arr)/sizeof(arr[0]);

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
                const int64_t p = u*v;
                const apz     S = apz::Add(U,V);
                const apz     D = apz::Sub(U,V);
                const apz     P = apz::Mul(U,V);
                int64_t       q=0;
                apz           Q;
                const bool testDiv = v>0;


                Y_ASSERT(s==S);
                Y_ASSERT(d==D);
                Y_ASSERT(p==P);
                Y_ASSERT(apz::Add(U,v)==S);
                Y_ASSERT(apz::Add(u,V)==S);

                Y_ASSERT(apz::Sub(U,v)==D);
                Y_ASSERT(apz::Sub(u,V)==D);

                Y_ASSERT(apz::Mul(U,v)==P);
                Y_ASSERT(apz::Mul(u,V)==P);

                if(testDiv)
                {
                    q = u/v;
                    Q = apz::Div(U,V);
                    Y_ASSERT(q==Q);
                    Y_ASSERT(apz::Div(U,v) == Q);
                    Y_ASSERT(apz::Div(u,V) == Q);
                }

                if(u>=0)
                {
                    const apn nu = Apex::natural_t(u);
                    Y_ASSERT(apz::Add(nu,V)==S);
                    Y_ASSERT(apz::Sub(nu,V)==D);
                    Y_ASSERT(apz::Mul(nu,V)==P);
                    if(testDiv)
                    {
                        Y_ASSERT(apz::Div(nu,V)==q);
                    }
                }

                if(v>=0)
                {
                    const apn nv = Apex::natural_t(v);
                    Y_ASSERT(apz::Add(U,nv)==S);
                    Y_ASSERT(apz::Sub(U,nv)==D);
                    Y_ASSERT(apz::Mul(U,nv)==P);
                    if( testDiv )
                    {
                        Y_ASSERT(apz::Div(U,nv) == Q);
                    }
                }

            }
        }

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


}
Y_UDONE()
