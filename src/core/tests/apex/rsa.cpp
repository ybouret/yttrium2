
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
    


}
Y_UDONE()

