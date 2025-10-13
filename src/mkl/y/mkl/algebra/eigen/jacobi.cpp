
#include "y/mkl/algebra/eigen.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/type/destroy.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/cameo/addition.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/api/fcpu.hpp"

namespace Yttrium
{
    namespace MKL
    {

#define real_t float
#define REAL(X) X##f
#include "jacobi.hxx"
#undef real_t
#undef REAL

#define real_t double
#define REAL(X) X
#include "jacobi.hxx"
#undef real_t
#undef REAL

#define real_t long double
#define REAL(X) X##L
#include "jacobi.hxx"
#undef real_t
#undef REAL


#define real_t XReal<float>
#define REAL(X) X##f
#include "jacobi.hxx"
#undef real_t
#undef REAL


#define real_t XReal<double>
#define REAL(X) X
#include "jacobi.hxx"
#undef real_t
#undef REAL

#define real_t XReal<long double>
#define REAL(X) X##L
#include "jacobi.hxx"
#undef real_t
#undef REAL

        

    }

}
