
#include "y/mkl/algebra/eigen.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/cameo/addition.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace MKL
    {
        
#define real_t float
#include "balance.hxx"
#undef real_t

#define real_t double
#include "balance.hxx"
#undef real_t

#define real_t long double
#include "balance.hxx"
#undef real_t

#define real_t XReal<float>
#include "balance.hxx"
#undef real_t

#define real_t XReal<double>
#include "balance.hxx"
#undef real_t

#define real_t XReal<long double>
#include "balance.hxx"
#undef real_t

    }
}

