
#include "y/mkl/fit/optimizer.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/type/destroy.hpp"
#include "y/mkl/numeric.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

#define real_t float
#define REAL(X) X##f
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<float>
#define REAL(X) X##f
#include "optimizer.hxx"
#undef real_t
#undef REAL

            
        }

    }

}


