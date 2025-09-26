
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

#define SAFETY_VALUE 0.9

#define real_t float
#include "driver.hxx"
#undef real_t

#define real_t double
#include "driver.hxx"
#undef real_t

#define real_t long double
#include "driver.hxx"
#undef real_t

#define real_t XReal<float>
#include "driver.hxx"
#undef real_t

#define real_t XReal<double>
#include "driver.hxx"
#undef real_t


#define real_t XReal<long double>
#include "driver.hxx"
#undef real_t

        }

    }

}

