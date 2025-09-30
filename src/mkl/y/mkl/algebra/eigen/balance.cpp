
#include "y/mkl/algebra/eigen.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/cameo/addition.hpp"
#include "y/type/destroy.hpp"
#include <cfloat>

namespace Yttrium
{
    namespace MKL
    {
        
#define real_t float
#define REAL(X) X##f
#include "balance.hxx"
#undef real_t
#undef REAL

#define real_t double
#define REAL(X) X
#include "balance.hxx"
#undef real_t
#undef REAL

#define real_t long double
#define REAL(X) X##L
#include "balance.hxx"
#undef real_t
#undef REAL

#define real_t XReal<float>
#define REAL(X) X##f
#include "balance.hxx"
#undef real_t
#undef REAL

#define real_t XReal<double>
#define REAL(X) X
#include "balance.hxx"
#undef real_t
#undef REAL

#define real_t XReal<long double>
#define REAL(X) X##L
#include "balance.hxx"
#undef real_t
#undef REAL

    }
}

