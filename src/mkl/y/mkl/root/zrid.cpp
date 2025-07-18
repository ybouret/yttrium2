

#include "y/mkl/root/zrid.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/half.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/ascii/boolean.hpp"

namespace Yttrium
{
    namespace MKL
    {
        static const char ZRidCallSign[] = "ZRid";

#define real_t float
#include "zrid.hxx"
#undef real_t


#define real_t double
#include "zrid.hxx"
#undef real_t

#define real_t long double
#include "zrid.hxx"
#undef real_t


#define real_t XReal<float>
#include "zrid.hxx"
#undef real_t

#define real_t XReal<double>
#include "zrid.hxx"
#undef real_t

#define real_t XReal<long double>
#include "zrid.hxx"
#undef real_t

    }

}
