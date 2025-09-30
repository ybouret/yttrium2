
#include "y/mkl/ode/explicit/driver.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/utils.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/mkl/api/fpow.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {


#define real_t float
#define REAL(X) X##f
#include "driver.hxx"
#undef real_t
#undef REAL

#define real_t double
#define REAL(X) X
#include "driver.hxx"
#undef real_t
#undef REAL

#define real_t long double
#define REAL(X) X##L
#include "driver.hxx"
#undef real_t
#undef REAL

#define real_t XReal<float>
#define REAL(X) X##f
#include "driver.hxx"
#undef real_t
#undef REAL

#define real_t XReal<double>
#define REAL(X) X
#include "driver.hxx"
#undef real_t
#undef REAL


#define real_t XReal<long double>
#define REAL(X) X##L
#include "driver.hxx"
#undef real_t

        }

    }

}

