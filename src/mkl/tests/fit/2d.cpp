#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif
#include "../../core/tests/main.hpp"

#include "y/mkl/fit/samples.hpp"
#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/string/env.hpp"
#include "y/string/boolean.hpp"

#include "y/mkl/fit/optimizer.hpp"


using namespace Yttrium;
using namespace MKL;


template <typename T> static inline
T getZ(const V2D<T> &X, const T radius, const V2D<T> &center)
{
    return radius - (X-center).norm();
}

template <typename T> static inline
T getF(const V2D<T> &X, const Fit::Variables &vars, const Readable<T> &aorg)
{
    const Fit::Variable &_r = vars["r"];
    const Fit::Variable &_x = vars["x"];
    const Fit::Variable &_y = vars["y"];

    const T      radius = aorg[_r.global.indx];
    const V2D<T> center( aorg[_x.global.indx], aorg[_y.global.indx] );
    return getZ<T>(X,radius,center);
}


template <typename T>
class CircleData
{
public:
    typedef V2D<T> VTX;
    typedef typename FCPU<T>::Type fcpu_t;

    explicit CircleData(Random::Bits &ran, const T radius) :
    n( ran.in<size_t>(3,100) ),
    center( ran.symm<fcpu_t>() * 10, ran.symm<fcpu_t>() * 10),
    p( WithAtLeast, n ),
    z( WithAtLeast, n )
    {
        static const fcpu_t one(1);
        static const fcpu_t err(0.05);


        const T dtheta = Twice(Numeric<T>::PI) / (fcpu_t)n;
        for(size_t i=0;i<n;++i)
        {
            const fcpu_t theta = ((fcpu_t) i) * dtheta * ( one + err * ran.symm<fcpu_t>() );
            const fcpu_t r     = radius * ( one + err * ran.symm<fcpu_t>() );
            const VTX    v( r * std::cos(theta), r * std::sin(theta) );
            p << v+center;
        }
    }

    const size_t n;
    const VTX    center;
    Vector<VTX>  p;
    Vector<T>    z;

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
