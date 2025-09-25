
#include "y/mkl/ode/explicit/driver.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/utils.hpp"
#include "y/mkl/api/fabs.hpp"

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
            

        }

    }

}

