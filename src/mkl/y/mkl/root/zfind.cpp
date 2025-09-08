#include "y/mkl/root/zfind.hpp"
#include "y/mkl/api/half.hpp"
#include "y/exception.hpp"
#include "y/mkl/xreal.hpp"

namespace Yttrium
{

    namespace MKL
    {

        static const char ZFindCallSign[] = "ZFind";

#define real_t float
#include "zfind.hxx"
#undef real_t


#define real_t double
#include "zfind.hxx"
#undef real_t

#define real_t long double
#include "zfind.hxx"
#undef real_t


#define real_t XReal<float>
#include "zfind.hxx"
#undef real_t

#define real_t XReal<double>
#include "zfind.hxx"
#undef real_t

#define real_t XReal<long double>
#include "zfind.hxx"
#undef real_t

    }
    
}

