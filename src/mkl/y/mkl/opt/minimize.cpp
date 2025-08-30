
#include "y/mkl/opt/minimize.hpp"
#include "y/mkl/xreal.hpp"
#include "y/system/exception.hpp"
#include "y/mkl/opt/optimize.hpp"
#include "y/mkl/opt/bracket.hpp"

namespace Yttrium
{
    namespace MKL
    {

        const char  * const Minimizing:: CallSign = "Minimize";

#define real_t float
#include "minimize.hxx"
#undef real_t

#define real_t double
#include "minimize.hxx"
#undef real_t

#define real_t long double
#include "minimize.hxx"
#undef real_t

#define real_t XReal<float>
#include "minimize.hxx"
#undef real_t

#define real_t XReal<double>
#include "minimize.hxx"
#undef real_t

#define real_t XReal<long double>
#include "minimize.hxx"
#undef real_t

    }
}
