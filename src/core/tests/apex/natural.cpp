
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

#if 1
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


    {
        std::cerr << "TwoToThePowerOf" << std::endl;
        for(size_t p=0;p<=80;++p)
        {
            Apex::Natural n(TwoToThePowerOf,p);
            std::cerr << n << std::endl;
            Y_ASSERT(1+p==n.bits());
            if(p<=63)
            {
                const uint64_t u = uint64_t(1) << p;
                Y_ASSERT(n==u);
            }
        }
    }


    {
        std::cerr << "Random" << std::endl;
        for(size_t p=0;p<=80;++p)
        {

            for(size_t i=0;i<4;++i)
            {
                const Apex::Natural n(ran,p);
                //std::cerr << n << std::endl;
                Y_ASSERT(n.bits()==p);
            }
        }
    }

    {
        std::cerr << "Add" << std::endl;
        for(size_t i=0;i<64;++i)
        {
            for(size_t j=0;j<64;++j)
            {
                const uint64_t l = ran.to<uint64_t>(i);
                const uint64_t r = ran.to<uint64_t>(j);
                const uint64_t s = l+r;
                Apex::Natural  L = l;
                Apex::Natural  R = r;

                //std::cerr << "L=" << L << std::endl;
                //std::cerr << "R=" << R << std::endl;

                for(unsigned u=0;u<Apex::Metrics::Views;++u)
                {
                    for(unsigned v=0;v<Apex::Metrics::Views;++v)
                    {
                        L.alter( Apex::ViewType(u) );
                        R.alter( Apex::ViewType(v) );

                        {
                            Apex::Natural S = L + R;
                            Y_ASSERT(S==s);
                        }

                    }
                }

            }
        }

    }





}
Y_UDONE()
