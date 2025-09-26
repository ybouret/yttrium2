#include "y/mkl/ode/explicit/integrator.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/cameo/addition.hpp"
#include "y/container/iter.hpp"
#include "y/core/utils.hpp"

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

