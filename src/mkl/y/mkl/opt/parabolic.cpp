#include "y/mkl/opt/parabolic.hpp"
#include "y/mkl/xreal.hpp"
#include "y/sorting/heap.hpp"
#include "y/core/display.hpp"

namespace Yttrium
{
    namespace MKL
    {

        bool ParabolicOptimizationVerbose = false;
        static const char PFX[] = "[ParabolicOptim] ";

#define Y_PRINT(MSG) do { if(ParabolicOptimizationVerbose) { std::cerr << PFX << MSG << std::endl; } } while(false)

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

