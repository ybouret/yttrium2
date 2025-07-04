#include "y/cameo/addition.hpp"
#include "y/cameo/summator/fpoint.hpp"
#include "y/cameo/summator/direct.hpp"
#include "y/cameo/summator/aproxy.hpp"


#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"

#include "y/check/static.hpp"

using namespace Yttrium;

namespace Yttrium
{

    namespace Cameo
    {

        
     

    }


}

Y_UTEST(cameo_add)
{

    {
        Cameo::DirectSummator<apz> zsum;
        Cameo::DirectSummator<apn> nsum;

        Cameo::AProxySummator<int>            isum; std::cerr << "isum/" <<Cameo::AProxySummator<int>::CoreType::CallSign << std::endl;
        Cameo::AProxySummator<unsigned short> usum; std::cerr << "usum/" <<Cameo::AProxySummator<unsigned short>::CoreType::CallSign << std::endl;

        Y_SIZEOF(Cameo::FPointSummator<float>::Accumulator);
        Y_SIZEOF(Cameo::FPointSummator< XReal<long double> >::Accumulator);

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
    }

}
Y_UDONE()



