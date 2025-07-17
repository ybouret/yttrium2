#include "y/mkl/root/zfind.hpp"
#include "y/mkl/api/half.hpp"
#include "y/system/exception.hpp"

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

    }
    
}

