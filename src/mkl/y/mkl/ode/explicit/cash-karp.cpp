
#include "y/mkl/ode/explicit/cash-karp.hpp"
#include "y/cameo/addition.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

#define real_t float
#include "cash-karp.hxx"
#undef real_t

        }

    }

}
