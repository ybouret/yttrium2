
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
                Y_ASSERT(n.bits()==p);
            }
        }
    }

    {
        std::cerr << "Additions 64" << std::endl;
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
                        const uint64_t l64 = L.ls64();
                        const uint64_t r64 = R.ls64();
                        Y_ASSERT( l64  == l);
                        Y_ASSERT( r64  == r);

                        {
                            Apex::Natural S = L + R;
                            Y_ASSERT(S==s);
                        }

                        {
                            Apex::Natural lhs = L; Y_ASSERT(lhs==L);
                            lhs.alter( Apex::ViewType(u)  );
                            R.alter( Apex::ViewType(v) );
                            lhs += R;
                            Y_ASSERT(lhs==s);
                        }

                        {
                            Apex::Natural lhs = L; Y_ASSERT(lhs==L);
                            lhs.alter( Apex::ViewType(u)  );
                            lhs += r;
                            Y_ASSERT(lhs==s);
                        }
                    }
                }
            }
        }
#if 1
        Apex::Natural n = 0;
        while(n<10)
        {
            std::cerr << ' ' << n++;
        }
        std::cerr << std::endl;
        n=0;
        while(n<10)
        {
            std::cerr << ' ' << ++n;
        }
        std::cerr << std::endl;
#endif
    }



    {
        std::cerr << "Subtractions 64" << std::endl;
        for(size_t i=0;i<64;++i)
        {
            for(size_t j=0;j<=i;++j)
            {
                uint64_t l = ran.to<uint64_t>(i);
                uint64_t r = ran.to<uint64_t>(j);
                if(r>l) Swap(l,r);
                Y_ASSERT(l>=r);
                const uint64_t d = l-r;
                Apex::Natural  L = l;
                Apex::Natural  R = r;

                for(unsigned u=0;u<Apex::Metrics::Views;++u)
                {
                    for(unsigned v=0;v<Apex::Metrics::Views;++v)
                    {
                        L.alter( Apex::ViewType(u) );
                        R.alter( Apex::ViewType(v) );

                        {
                            Apex::Natural D = L - R;
                            Y_ASSERT(D==d);
                        }

                        {
                            Apex::Natural D = L - r;
                            Y_ASSERT(D==d);
                        }

                        {
                            Apex::Natural D = l - R;
                            Y_ASSERT(D==d);
                        }

                        {
                            Apex::Natural lhs = L; Y_ASSERT(lhs==L);
                            lhs.alter( Apex::ViewType(u)  );
                            R.alter( Apex::ViewType(v) );
                            lhs -= R;
                            Y_ASSERT(lhs==d);
                        }

                        {
                            Apex::Natural lhs = L; Y_ASSERT(lhs==L);
                            lhs.alter( Apex::ViewType(u)  );
                            lhs -= r;
                            Y_ASSERT(lhs==d);
                        }
                    }
                }
            }
            
        }

        Apex::Natural n = 10;
        while(n!=0)
        {
            std::cerr << ' ' << n--;
        }
        std::cerr << std::endl;
        n = 10;
        while(n!=0)
        {
            std::cerr << ' ' << --n;
        }
        std::cerr << std::endl;
    }


    {
        std::cerr << "AddSub" << std::endl;
        for(size_t iter=0;iter<10;++iter)
        {
            Apex::Natural l(ran, ran.leq(1000) );
            Apex::Natural r(ran, ran.leq(1000) );
            Apex::Natural s = l+r;
            Y_ASSERT(s-l == r);
            Y_ASSERT(s-r == l);
        }
    }
}
Y_UDONE()
