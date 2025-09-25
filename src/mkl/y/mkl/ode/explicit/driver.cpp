
#include "y/mkl/ode/explicit/driver.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/utils.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/fcpu.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

#define SAFETY_VALUE 0.9

#define real_t float
#define REAL(X) X##f
#include "driver.hxx"
#undef real_t
#undef REAL
            

        }

    }

}

