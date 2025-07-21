#include "y/mkl/opt/parabolic.hpp"
#include "y/mkl/xreal.hpp"
#include "y/sorting/heap.hpp"
#include "y/core/display.hpp"

namespace Yttrium
{
    namespace MKL
    {

        

#define real_t float
#include "parabolic.hxx"
#undef real_t

#define real_t double
#include "parabolic.hxx"
#undef real_t

#define real_t long double
#include "parabolic.hxx"
#undef real_t

#define real_t XReal<float>
#include "parabolic.hxx"
#undef real_t

#define real_t XReal<double>
#include "parabolic.hxx"
#undef real_t

#define real_t XReal<long double>
#include "parabolic.hxx"
#undef real_t


    }

}

