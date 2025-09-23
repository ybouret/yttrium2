
#include "y/mkl/algebra/eigen.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/fabs.hpp"
//#include "y/cameo/addition.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace MKL
    {

#define real_t float
#include "hessenberg.hxx"
#undef real_t


    }

}

