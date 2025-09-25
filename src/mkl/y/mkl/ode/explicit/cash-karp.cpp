
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



            
#define FOREACH_I for(size_t i=n;i>0;--i)

#define real_t float
#define REAL(X) X##f
#include "cash-karp.hxx"
#undef real_t
#undef REAL

#define real_t double
#define REAL(X) X
#include "cash-karp.hxx"
#undef real_t
#undef REAL


#define real_t XReal<float>
#define REAL(X) real_t(X##f)
#include "cash-karp.hxx"
#undef real_t

        }

    }

}
