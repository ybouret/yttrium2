
#include "y/mkl/fit/adjustable/engine.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

#define real_t float
#include "engine.hxx"
#undef real_t


#define real_t double
#include "engine.hxx"
#undef real_t

#define real_t long double
#include "engine.hxx"
#undef real_t


#define real_t XReal<float>
#include "engine.hxx"
#undef real_t

#define real_t XReal<double>
#include "engine.hxx"
#undef real_t

#define real_t XReal<long double>
#include "engine.hxx"
#undef real_t


        }

    }

}


