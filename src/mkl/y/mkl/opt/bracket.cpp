#include "y/mkl/opt/bracket.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/almost-equal.hpp"

namespace Yttrium
{
    namespace MKL
    {

#define real_t float
#include "bracket.hxx"
#undef real_t

#define real_t double
#include "bracket.hxx"
#undef real_t

#define real_t long double
#include "bracket.hxx"
#undef real_t

#define real_t XReal<float>
#include "bracket.hxx"
#undef real_t

#define real_t XReal<double>
#include "bracket.hxx"
#undef real_t

#define real_t XReal<long double>
#include "bracket.hxx"
#undef real_t
    }

}
