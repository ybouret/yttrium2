
#include "y/apex/n/modular.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/calculus/ipower.hpp"


using namespace Yttrium;

Y_UTEST(apex_rsa)
{

    Random::ParkMiller ran;

    std::cerr << "Modular Exp" << std::endl;
    for(size_t ib=0;ib<=30;++ib)
    {

        for(size_t ie=0;ie<=4;++ie)
        {

            for(size_t in=1;in<=20;++in)
            {
                const apn b(ran,ib);
                const apn e(ran,ie);
                const apn n(ran,in);

                //(std::cerr << b << '^' << e << " [" << n << "] = ").flush();
                const apn prd = ipower(b,e.ls64());
                const apn raw = prd  % n;
                //(std::cerr << raw).flush();
                const apn alg = Apex::Modular::Exp(b,e,n);
                //std::cerr << " -> " << alg << std::endl;
                Y_ASSERT(alg==raw);
            }
        }
    }

    std::cerr << "Modular Inv" << std::endl;
    for(size_t in=1;in<=40;in += 1+ran.leq<size_t>(8))
    {
        for(size_t ia=1;ia<=10;++ia)
        {
            apn        n(ran,in);
            const apn  a(ran,ia);
            while( a>=n || 1 != apn::GCD(n,a) ) ++n;
            const apn b = Apex::Modular::Inv(a,n);
            const apn r = (a*b) % n;
            Y_ASSERT(1==r);
        }
    }


    {
        const apn p = 11;
        const apn q = 23;
        const apn n = p*q;
        std::cerr << "n=" << n << std::endl;
        const apn phi = (p-1)*(q-1);
        const apn e   = 7;
        const apn d   = Apex::Modular::Inv(e,phi);
        std::cerr << "e=" << e << ", d=" << d << std::endl;

        for(apn M=0;M<n;++M)
        {
            std::cerr << "M=" << std::setw(6) << M;
            const apn C = Apex::Modular::Exp(M,e,n);
            std::cerr << " => C=" << std::setw(6) << C;
            const apn D = Apex::Modular::Exp(C,d,n);
            std::cerr << " => D=" << std::setw(6) << D;
            std::cerr << std::endl;
            Y_ASSERT(D==M);
        }
    }

}
Y_UDONE()

