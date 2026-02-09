
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/apex/ratsimp.hpp"
#include "y/utest/run.hpp"
#include "y/container/matrix.hpp"
#include "y/container/cxx/array.hpp"
#include "../main.hpp"


using namespace Yttrium;

Y_UTEST(apex_ratsimp)
{
    Random::MT19937 ran;

    for(size_t n=1;n<=5;++n)
    {
        CxxArray<apq> arr(n);
        CxxArray<apz> zrr(n);

        {
            const apq d = Apex::RatSimp::LCD(arr);
            Y_ASSERT(1==d);
        }

        FillWith<apq>::Seq(ran,arr);
        std::cerr << arr << " = ";


        const apn denom = Apex::RatSimp::Array(arr);
        for(size_t i=n;i>0;--i)
        {
            Y_ASSERT(1==arr[i].denom);
            zrr[i] = arr[i].numer;
        }
        const apn numer = Apex::Simplify::Array(zrr);

        const apq q(numer,denom);
        std::cerr << q << " * " << zrr << std::endl;





    }
}
Y_UDONE()
