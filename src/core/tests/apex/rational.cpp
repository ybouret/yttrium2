

#include "y/apex/rational.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(apex_q)
{

    { const apq q; std::cerr << q << std::endl; }

    { const apq q(-3,9); std::cerr << q << std::endl; }

    {
        static const Fraction F[] =
        {
            {-1,3}, {0,1}, {6,5}
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
            const apq gt1 = F[2];
            std::cerr << one << std::endl;
            const apn _1 = 1;
            Y_CHECK( __Zero__ == apq::Compare(one,_1) );
            Y_CHECK( __Zero__ == apq::Compare(_1,one) );
            Y_CHECK( Positive == apq::Compare(gt1,_1) );
            Y_CHECK( Negative == apq::Compare(_1,gt1) );

        }

    }

}
Y_UDONE()

