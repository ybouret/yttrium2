#include "y/cameo/addition.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "../main.hpp"
#include "y/utest/run.hpp"
#include <typeinfo>

using namespace Yttrium;

namespace {
    template <typename T> static inline
    void testXAdd(Random::Bits &ran)
    {
        Cameo::Addition<T> xadd;
        std::cerr << "Genus: " << xadd.callSign() << "@" << typeid(T).name() <<  std::endl;

        T s(0);
        const size_t n =ran.leq<size_t>(20);
        std::cerr << "\tcount=" << n << std::endl;
        std::cerr << '[';
        for(size_t i=n;i>0;--i)
        {
            const T x = Gen<T>::New(ran);
            xadd << x;
            s += x;
            //std::cerr << ' ' << x;
        }
        std::cerr << ' ' << ']' << std::endl;
        try
        {
            const T S = xadd.sum();
            std::cerr << "\t" << s << " -> " << S << std::endl;
        }
        catch(const Exception &excp)
        {
            excp.show(std::cerr);
        }
        catch(...)
        {
            throw;
        }
    }

}

Y_UTEST(cameo_add)
{

    Random::MT19937 ran;

    testXAdd<apn>(ran);
    testXAdd<apz>(ran);
    testXAdd<apq>(ran);

    testXAdd<int>(ran);
    testXAdd<uint16_t>(ran);

    testXAdd<float>(ran);
    return 0;
    testXAdd<double>(ran);
    testXAdd<long double>(ran);

    testXAdd< XReal<float> >(ran);
    testXAdd< XReal<double> >(ran);
    testXAdd< XReal<long double> >(ran);

    testXAdd< Complex<float> >(ran);
    testXAdd< Complex<double> >(ran);
    testXAdd< Complex<long double> >(ran);

#if 0
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
#endif

}
Y_UDONE()



