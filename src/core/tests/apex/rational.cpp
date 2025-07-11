

#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;

namespace
{
    template <typename T> static inline
    void genericOps(const T        arr[],
                    const size_t   num,
                    Random::Bits & ran)
    {
        std::cerr << "---- generic ops --" << std::endl;
        for(size_t i=0;i<num;++i)
        {
            const T  &x = arr[i]; // original
            const apq q = x;      // as rational
            std::cerr << "Using " << x << " (= " << q << ")" << std::endl << "\t";
            for(size_t nbit=0;nbit<=3;++nbit)
            {
                for(size_t dbit=1;dbit<=4;++dbit)
                {
                    const apq r(ran,nbit,dbit);
                    std::cerr << " " << r;

                    Y_ASSERT(apq::Compare(r,q) == apq::Compare(r,x));
                    Y_ASSERT(apq::Compare(q,r) == apq::Compare(x,r));

                    {
                        const apq sum = apq::Add(q,r); Y_ASSERT( apq::Add(r,q) == sum );
                        Y_ASSERT( apq::Add(r,x) == sum );
                        Y_ASSERT( apq::Add(x,r) == sum );
                    }

                    {
                        const apq dif = apq::Sub(q,r); Y_ASSERT( apq::Sub(r,q) == -dif );
                        Y_ASSERT( apq::Sub(r,x) == -dif );
                        Y_ASSERT( apq::Sub(x,r) == dif );
                    }

                    if(nbit<=0) break;
                }
            }
            std::cerr << std::endl;
        }
    }
}

Y_UTEST(apex_q)
{

    Random::ParkMiller ran;

    {
        std::cerr << "Default..." << std::endl;
        const apq q; std::cerr << q << std::endl; }

    {
        std::cerr << "Special..." << std::endl;
        apq q(-3,9); std::cerr << q << std::endl;
    }

    {
        std::cerr << "Specific comparisons..." << std::endl;
        static const Fraction F[] =
        {
            {-1,3}, {0,1}, {1,7}, {6,5}
        };
        static const size_t num = sizeof(F)/sizeof(F[0]);

        for(size_t i=0;i<num;++i)
        {
            const apq    I  = F[i];
            const double xi = double(F[i].numer) / F[i].denom;
            for(size_t j=1;j<num;++j)
            {
                const apq J = F[j];
                const double xj = double(F[j].numer) / F[j].denom;

                const SignType cmp = Sign::Of(xi,xj);
                Y_ASSERT( apq::Compare(I,J) == cmp);
            }
        }

        {
            const apq one = 1;
            const apq lt1 = F[2];
            const apq gt1 = F[3];
            std::cerr << one << std::endl;
            const apn _1 = 1;
            Y_CHECK( __Zero__ == apq::Compare(one,_1) );
            Y_CHECK( __Zero__ == apq::Compare(_1,one) );
            Y_CHECK( Positive == apq::Compare(gt1,_1) );
            Y_CHECK( Negative == apq::Compare(_1,gt1) );
        }
    }

    {
        std::cerr << "Generic Comparisons" << std::endl;

        {
            const apn arr[] = { apn(0), apn(1) };
            genericOps(arr,sizeof(arr)/sizeof(arr[0]),ran);
        }

        {
            const apz arr[] = { apz(-1), apz(0), apz(1) };
            genericOps(arr,sizeof(arr)/sizeof(arr[0]),ran);
        }

        {
            const int arr[] = { -1,0,1 };
            genericOps(arr,sizeof(arr)/sizeof(arr[0]),ran);
        }

    }

    {
        for(apq q(-23,7);q <= 3; )
        {
            std::cerr << ' ' << ++q;
        }
        std::cerr << std::endl;

        for(apq q(-23,7);q <= 3; )
        {
            std::cerr << ' ' << q++;
        }
        std::cerr << std::endl;
    }

    {
        for(apq q(14,3); q >= -4; )
        {
            std::cerr << ' ' << --q;
        }
        std::cerr << std::endl;
        for(apq q(14,3); q >= -4; )
        {
            std::cerr << ' ' << q--;
        }
        std::cerr << std::endl;
    }

}
Y_UDONE()

