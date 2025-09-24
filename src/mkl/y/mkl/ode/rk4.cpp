
#include "y/mkl/ode/rk4.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/cameo/addition.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {

#define real_t float
#include "rk4.hxx"
#undef real_t

#define real_t double
#include "rk4.hxx"
#undef real_t

#define real_t long double
#include "rk4.hxx"
#undef real_t


#define real_t XReal<float>
#include "rk4.hxx"
#undef real_t

#define real_t XReal<double>
#include "rk4.hxx"
#undef real_t

#define real_t XReal<long double>
#include "rk4.hxx"
#undef real_t
            
        }
    }
}
