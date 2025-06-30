
#include "y/mkl/xreal.hpp"
#include "y/system/exception.hpp"
#include "y/mkl/numeric.hpp"
#include "y/string/format.hpp"

#include <cerrno>
#include <cmath>

namespace Yttrium
{
    Y_Shallow_Impl(Raised);
    XRealOutput::ModeType XRealOutput::Mode = XRealOutput::Default;
}

#define real_t float
#include "xreal.hxx"

#undef real_t
#define real_t double
#include "xreal.hxx"

#undef real_t
#define real_t long double
#include "xreal.hxx"

