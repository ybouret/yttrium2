
#include "y/mkl/algebra/eigen.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/type/destroy.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace MKL
    {

#define real_t float
#include "hessenberg.hxx"
#undef real_t

#define real_t double
#include "hessenberg.hxx"
#undef real_t

#define real_t long double
#include "hessenberg.hxx"
#undef real_t

#define real_t XReal<float>
#include "hessenberg.hxx"
#undef real_t

#define real_t XReal<double>
#include "hessenberg.hxx"
#undef real_t

#define real_t XReal<long double>
#include "hessenberg.hxx"
#undef real_t

#define real_t apq
#include "hessenberg.hxx"
#undef real_t

    }

}

