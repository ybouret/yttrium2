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
            std::cerr << ' ' << x;
        }
        std::cerr << ' ' << ']' << std::endl;
        try
        {
            const T S = xadd.sum();
            const T delta = S-s;
            std::cerr << "\t" << s << " -> " << S << ", delta=" << delta << std::endl;
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
    testXAdd<double>(ran);
    testXAdd<long double>(ran);

    testXAdd< XReal<float> >(ran);
    testXAdd< XReal<double> >(ran);
    testXAdd< XReal<long double> >(ran);

    testXAdd< Complex<float> >(ran);
    testXAdd< Complex<double> >(ran);
    testXAdd< Complex<long double> >(ran);

    testXAdd< V3D<double> >(ran);


}
Y_UDONE()



