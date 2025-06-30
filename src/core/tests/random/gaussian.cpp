#include "y/random/gaussian.hpp"

#include "y/random/isaac.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/park-miller.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include <typeinfo>

using namespace Yttrium;


namespace {


    template <typename T> static inline
    void testGaussian( Random::SharedBits &bits, const size_t n)
    {
        Random::Gaussian<T> gran( bits );

        Vector<T> data(WithAtLeast,n);

        for(size_t i=0;i<n;++i) data << gran();

        T sum = 0;
        for(size_t i=1;i<=n;++i) sum += data[i];
        const T ave = sum / T(n);
        std::cerr << "\tave=" << ave << std::endl;
        T var = 0;
        for(size_t i=1;i<=n;++i)
        {
            const T del = data[i] - ave;
            var += del * del;
        }
        var /= n;
        std::cerr << "\tvar=" << var << std::endl;

    }

}


Y_UTEST(random_gaussian)
{
    typedef Random::Alea<float>::Type           floatType;
    typedef Random::Alea< XReal<double> >::Type XDoubleType;

    std::cerr << typeid(floatType).name()   << std::endl;
    std::cerr << typeid(XDoubleType).name() << std::endl;

    Random::SharedBits bits = new Random::MT19937();
    size_t             n    = 10000;

    testGaussian<float>(bits,n);
    testGaussian< XReal<long double> >(bits,n);



}
Y_UDONE()

