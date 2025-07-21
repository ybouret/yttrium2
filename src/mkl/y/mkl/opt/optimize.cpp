
#include "y/mkl/opt/optimize.hpp"
#include "y/mkl/opt/parabolic.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"

namespace Yttrium
{
    namespace MKL
    {
#define real_t float
#include "optimize.hxx"
#undef real_t

#define real_t double
#include "optimize.hxx"
#undef real_t

#define real_t long double
#include "optimize.hxx"
#undef real_t

#define real_t XReal<float>
#include "optimize.hxx"
#undef real_t

#define real_t XReal<double>
#include "optimize.hxx"
#undef real_t

#define real_t XReal<long double>
#include "optimize.hxx"
#undef real_t

    }
}


