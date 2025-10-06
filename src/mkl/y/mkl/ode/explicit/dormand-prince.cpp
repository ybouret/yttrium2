

#include "y/mkl/ode/explicit/dormand-prince.hpp"
#include "y/cameo/addition.hpp"
#include "y/type/destroy.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace ODE
        {


            static const char * const DormandPrinceID = "Dormand-Prince";

#define FOREACH_I for(size_t i=n;i>0;--i)

#define real_t float
#define REAL(X) X##f
#include "dormand-prince.hxx"
#undef real_t
#undef REAL

#define real_t double
#define REAL(X) X
#include "dormand-prince.hxx"
#undef real_t
#undef REAL

#define real_t long double
#define REAL(X) X##L
#include "dormand-prince.hxx"
#undef real_t
#undef REAL


#define real_t XReal<float>
#define REAL(X) real_t(X##f)
#include "dormand-prince.hxx"
#undef real_t
#undef REAL

#define real_t XReal<double>
#define REAL(X) real_t(X)
#include "dormand-prince.hxx"
#undef real_t
#undef REAL

#define real_t XReal<long double>
#define REAL(X) real_t(X##L)
#include "dormand-prince.hxx"
#undef real_t
#undef REAL

        }

    }

}
