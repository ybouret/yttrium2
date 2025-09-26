#include "y/mkl/ode/explicit/integrator.hpp"
#include "y/mkl/ode/explicit/driver.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/cameo/addition.hpp"
#include "y/container/iter.hpp"
#include "y/core/utils.hpp"
#include "y/exception.hpp"
#include "y/mkl/numeric.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

#define real_t float
#include "integrator.hxx"
#undef real_t

        }
    }

}

