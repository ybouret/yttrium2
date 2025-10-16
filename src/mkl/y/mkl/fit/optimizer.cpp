
#include "y/mkl/fit/optimizer.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/type/destroy.hpp"
#include "y/mkl/numeric.hpp"
#include "y/field/1d.hpp"
#include "y/mkl/api/fcpu.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

#define real_t float
#define REAL(X) X##f
#include "optimizer.hxx"
#undef real_t
#undef REAL


#define real_t double
#define REAL(X) X
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t long double
#define REAL(X) X##L
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<float>
#define REAL(X) X##f
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<double>
#define REAL(X) X
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<long double>
#define REAL(X) X##L
#include "optimizer.hxx"
#undef real_t
#undef REAL

        }

    }

}


