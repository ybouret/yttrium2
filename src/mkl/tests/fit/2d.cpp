#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/fit/samples.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/string/env.hpp"
#include "y/string/boolean.hpp"

#include "y/mkl/fit/optimizer.hpp"

#include "../../core/tests/main.hpp"

using namespace Yttrium;
using namespace MKL;

template <typename T>
class CircleData
{
public:
    typedef V2D<T> VTX;
    typedef typename FCPU<T>::Type fcpu_t;

    explicit CircleData(Random::Bits &ran, const T radius) :
    n( ran.in<size_t>(3,100) ),
    p( WithAtLeast, n )
    {
        const fcpu_t one(1);
        const fcpu_t err(0.05);

        const T dtheta = Twice(Numeric<T>::PI) / (fcpu_t)n;
        for(size_t i=0;i<n;++i)
        {
            const fcpu_t theta = ((fcpu_t) i) * dtheta * ( one + err * ran.symm<fcpu_t>() );
            const fcpu_t r     = radius * ( one + err * ran.symm<fcpu_t>() );
            const VTX    v( r * std::cos(theta), r * std::sin(theta) );
            p << v;
        }
    }

    const size_t n;
    Vector<VTX>  p;

private:
    Y_Disable_Copy_And_Assign(CircleData);
};

template <typename T> static inline
void Test2D(Random::Bits &ran)
{
    typedef V2D<T> VTX;

    CircleData<T>       C1(ran,1.2f);
    Fit::Samples<VTX,T> samples("Cs");

}


Y_UTEST(fit_2d)
{
    Random::MT19937 ran;

    Test2D<float>(ran);
    //Test2D< XReal<float> >(ran);

}
Y_UDONE()
