
#include "y/mkl/algebra/eigen.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/fabs.hpp"
#include "y/type/destroy.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/cameo/addition.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/mkl/api/almost-equal.hpp"
//#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace MKL
    {

#define real_t float
#include "jacobi.hxx"
#undef real_t


#define real_t double
#include "jacobi.hxx"
#undef real_t

#define real_t long double
#include "jacobi.hxx"
#undef real_t


#define real_t XReal<float>
#include "jacobi.hxx"
#undef real_t
        
#if 0

#define real_t XReal<double>
#include "jacobi.hxx"
#undef real_t

#define real_t XReal<long double>
#include "jacobi.hxx"
#undef real_t
#endif
        

    }

}
