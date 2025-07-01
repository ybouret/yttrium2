
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/hexadecimal.hpp"

using namespace Yttrium;



Y_UTEST(apex_n)
{
    Random::ParkMiller ran;

    {
        std::cerr << "Default" << std::endl;
        Apex::Natural n;
        std::cerr << n << std::endl;
        Y_CHECK(0==n);
        Y_CHECK(n==0);
    }


    {
        std::cerr << "Comparisons" << std::endl;
        for(size_t i=0;i<1000;++i)
        {
            const uint64_t      l = ran.to<uint64_t>( ran.leq(64) );
            const uint64_t      r = ran.to<uint64_t>( ran.leq(64) );
            Apex::Natural       L = l;
            Apex::Natural       R = r;
            Y_ASSERT(L==L);
            const SignType      s  = Sign::Of(l,r);
            const SignType      S  = Apex::Natural::Compare(L,R);
            const SignType      s1 = Apex::Natural::Compare(l,R);
            const SignType      s2 = Apex::Natural::Compare(L,r);
            //std::cerr << Hexadecimal(l) << " / " << Hexadecimal(r) << " : " << s << " / " << s1 << " / " << s2 << std::endl;
            Y_ASSERT(s==S);
            Y_ASSERT(s==s1);
            Y_ASSERT(s==s2);

#if 0
            for(unsigned j=0;j<Apex::Metrics::Views;++j)
            {
                for(unsigned k=0;k<Apex::Metrics::Views;++k)
                {
                    L.alter( Apex::ViewType(j) );
                    R.alter( Apex::ViewType(k) );
                    Y_ASSERT( Apex::Natural::Compare(L,R) == S);
                }
            }
#endif

        }
    }
    return 0;

    {
        Apex::Natural n = 0x234;
        std::cerr << n << std::endl;
        n = 0xabcde;
        std::cerr << n << std::endl;
    }

    for(size_t p=0;p<=80;++p)
    {
        Apex::Natural n(TwoToThePowerOf,p);
        std::cerr << n << std::endl;
    }

    for(size_t p=0;p<=80;++p)
    {
        for(size_t i=0;i<4;++i)
        {
            Apex::Natural n(ran,p);
            std::cerr << n << std::endl;
        }
    }

}
Y_UDONE()
