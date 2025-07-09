
#include "y/apex/natural.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/apex/metrics.hpp"

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
        std::cerr << "Comparisons...." << std::endl;
        for(size_t i=0;i<1000;++i)
        {
            const uint64_t      l = ran.to<uint64_t>( ran.leq<unsigned>(64) );
            const uint64_t      r = ran.to<uint64_t>( ran.leq<unsigned>(64) );
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
            for(unsigned j=0;j<Apex::Metrics::Plans;++j)
            {
                for(unsigned k=0;k<Apex::Metrics::Plans;++k)
                {
                    L.alter( Apex::PlanType(j) );
                    R.alter( Apex::PlanType(k) );
                    Y_ASSERT( Apex::Natural::Compare(L,R) == S);
                }
            }
#endif

        }
    }

    {
        std::cerr << "TwoToThePowerOf..." << std::endl;
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

                for(unsigned u=0;u<Apex::Metrics::Plans;++u)
                {
                    for(unsigned v=0;v<Apex::Metrics::Plans;++v)
                    {
                        L.alter( Apex::PlanType(u) );
                        R.alter( Apex::PlanType(v) );
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
                            lhs.alter( Apex::PlanType(u)  );
                            R.alter( Apex::PlanType(v) );
                            lhs += R;
                            Y_ASSERT(lhs==s);
                        }

                        {
                            Apex::Natural lhs = L; Y_ASSERT(lhs==L);
                            lhs.alter( Apex::PlanType(u)  );
                            lhs += r;
                            Y_ASSERT(lhs==s);
                        }
                    }
                }
            }
        }

        
        Apex::Natural n(0);
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

                for(unsigned u=0;u<Apex::Metrics::Plans;++u)
                {
                    for(unsigned v=0;v<Apex::Metrics::Plans;++v)
                    {
                        L.alter( Apex::PlanType(u) );
                        R.alter( Apex::PlanType(v) );

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
                            lhs.alter( Apex::PlanType(u)  );
                            R.alter( Apex::PlanType(v) );
                            lhs -= R;
                            Y_ASSERT(lhs==d);
                        }

                        {
                            Apex::Natural lhs = L; Y_ASSERT(lhs==L);
                            lhs.alter( Apex::PlanType(u)  );
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
            Apex::Natural l(ran, ran.leq<unsigned>(1000) );
            Apex::Natural r(ran, ran.leq<unsigned>(1000) );
            Apex::Natural s = l+r;
            Y_ASSERT(s-l == r);
            Y_ASSERT(s-r == l);
        }
    }
    
    {
        std::cerr << "SHR" << std::endl;
        for(size_t i=0;i<=80;++i)
        {
            Apex::Natural n(TwoToThePowerOf,i);
            std::cerr << n << " = 2^" << i << std::endl;
            for(size_t j=1;j<=i;++j)
            {
                n.shr();
                std::cerr << n << "/";
                Y_ASSERT( n == apn(TwoToThePowerOf,i-j) );
            }
            n.shr();
            std::cerr << n << std::endl;
            Y_ASSERT( 0 == n );
        }
        apn lhs = 12;
        lhs += 14;
        lhs.shr();
        Y_CHECK(13==lhs);
    }

    {
        std::cerr << "Mul64" << std::endl;
        for(size_t i=0;i<=32;++i)
        {
            for(size_t j=0;j<=32;++j)
            {
                for(size_t iter=0;iter<100;++iter)
                {
                    const uint64_t l = ran.to<uint64_t>(i);
                    const uint64_t r = ran.to<uint64_t>(j);
                    const uint64_t p = l*r;
                    const apn      L = l;
                    const apn      R = r;
                    const apn      P = L*R;
                    Y_ASSERT(P==p);
                    Y_ASSERT(P==r*L);
                    Y_ASSERT(P==R*l);
                }
            }
        }
    }
    
    {
        std::cerr << "Div64 [";


        for(size_t j=1;j<=64;++j)
        {
            (std::cerr << '.').flush();
            for(size_t i=0;i<=64;++i)
            {

                for(size_t iter=0;iter<4;++iter)
                {
                    const uint64_t numer = ran.to<uint64_t>(i);
                    const uint64_t denom = ran.to<uint64_t>(j);
                    const uint64_t q     = numer/denom;
                    const uint64_t r     = numer%denom;

                    //std::cerr << numer << " = " << q << " * " << denom << " + " << r << std::endl;

                    const apn N = numer;
                    const apn D = denom;
                    apn Q,R;
                    Apex::Natural::Div_(&Q,&R,N,D);
                    Y_ASSERT(q==Q);
                    Y_ASSERT(r==R);

                    Q = N/D;         Y_ASSERT(q==Q);
                    R = N%D;         Y_ASSERT(r==R);
                    Q = N; Q/=D;     Y_ASSERT(q==Q);
                    Q = N; Q/=denom; Y_ASSERT(q==Q);
                    R = N; R%=D;     Y_ASSERT(r==R);
                    R = N; R%=denom; Y_ASSERT(r==R);
                }
            }

        }
        std::cerr << "]" << std::endl;
    }

    {
        std::cerr << "MulDiv" << std::endl;
        for(size_t iter=0;iter<10;++iter)
        {
            const Apex::Natural l(ran, 1+ran.leq<unsigned>(1000) );
            const Apex::Natural r(ran, 1+ran.leq<unsigned>(1000) );
            const Apex::Natural p = l*r;
            Y_ASSERT(p/l==r);
            Y_ASSERT(p/r==l);
        }
    }
    
#if 1
    {
        std::cerr << "Sqrt" << std::endl;
        for(apn i=0;i<=100;++i)
        {
            const apn s = i.sqrt();
            std::cerr << i << " => " << s << std::endl;
            Y_ASSERT(s*s<=i);
            Y_ASSERT((s+1)*(s+1)>i);
        }
    }
#endif
    
}
Y_UDONE()
