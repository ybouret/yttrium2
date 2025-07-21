#include "y/mkl/opt/parabolic.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/sorting/heap.hpp"
#include "y/core/display.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{
    namespace MKL
    {

        bool              ParabolicStepVerbose = false;
        static const char PFX[] = "[ParabolicStep] ";

#define Y_PRINT(MSG) do { \
if(ParabolicStepVerbose) { std::cerr << PFX << MSG << std::endl; } \
} while(false)



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

