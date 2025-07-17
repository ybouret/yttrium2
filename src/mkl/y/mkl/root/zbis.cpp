
#include "y/mkl/root/zbis.hpp"
#include "y/mkl/xreal.hpp"
#include "y/mkl/api/half.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/ascii/boolean.hpp"

namespace Yttrium
{
    namespace MKL
    {
        static const char ZBisCallSign[] = "ZBis";

#define real_t float
#include "zbis.hxx"
#undef real_t


#define real_t double
#include "zbis.hxx"
#undef real_t

#define real_t long double
#include "zbis.hxx"
#undef real_t


#define real_t XReal<float>
#include "zbis.hxx"
#undef real_t

#define real_t XReal<double>
#include "zbis.hxx"
#undef real_t

#define real_t XReal<long double>
#include "zbis.hxx"
#undef real_t
        
    }

}
