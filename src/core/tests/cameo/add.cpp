#include "y/cameo/addition.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "../main.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;


Y_UTEST(cameo_add)
{

    Random::MT19937 ran;

    {
        std::cerr << Gen< Complex<float> >:: New(ran) << std::endl;
        std::cerr << Gen< Complex< XReal<long double> > >:: New(ran) << std::endl;
    }

    return 0;

    {
        Cameo::DirectSummator<apz> zsum;
        Cameo::DirectSummator<apn> nsum;

        Cameo::AProxySummator<int>            isum; std::cerr << "isum/" <<Cameo::AProxySummator<int>::CoreType::CallSign << std::endl;
        Cameo::AProxySummator<unsigned short> usum; std::cerr << "usum/" <<Cameo::AProxySummator<unsigned short>::CoreType::CallSign << std::endl;


        Cameo::FPointSummator< float > fsum(5);
        std::cerr << fsum->capacity() << std::endl;
        fsum->ensure(10);
        std::cerr << fsum->capacity() << std::endl;

        fsum->release();

        fsum << -0.01f << 0.02f << 1.0f << -1.2f;

        //std::cerr << "fsum=" << fsum << std::endl;
        std::cerr << "Computing" << std::endl;
        const float s = fsum.sum();
        std::cerr << "s=" << s << std::endl;


        Cameo::FPointSummator< XReal<long double> > xsum(5);
        xsum << -0.01 << 0.02 << 1 << -1.2;
        std::cerr << "Computing" << std::endl;
        const  XReal<long double> x = xsum.sum();
        std::cerr << "x=" << x << std::endl;

        Cameo::FPointSummator< Complex<double> > csum(5);
        csum << -0.01 << 0.02 << 1 << -1.2;
        std::cerr << "Computing" << std::endl;
        const Complex<double> c = csum.sum();
        std::cerr << "c=" << c << std::endl;
    }

    {
        Cameo::Addition<apz>                zsum;
        Cameo::Addition<apn>                nsum;
        Cameo::Addition<int>                isum;
        Cameo::Addition<unsigned>           usum;
        Cameo::Addition<float>              fsum;
        Cameo::Addition< XReal<double> >    xsum;
        Cameo::Addition< Complex<double> >  csum;
        Cameo::Addition< Complex< XReal<long double> > >  xcsum;
    }


    {
        Cameo::VectorialSummator< Complex<float> > csum;
        csum << Complex<float>(0.1f,0.2f);

    }
}
Y_UDONE()



