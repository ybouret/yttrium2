
#include "y/mkl/fit/optimizer.hpp"
#include "y/mkl/tao/1.hpp"


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            const char * const OptimizerCommon:: CallSign = "Fit::Optimizer";
            OptimizerCommon::  OptimizerCommon() noexcept {}
            OptimizerCommon:: ~OptimizerCommon() noexcept {}


#define real_t float
#define REAL(X) X##f
#include "optimizer.hxx"
#undef real_t
#undef REAL


#define real_t double
#define REAL(X) X
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t long double
#define REAL(X) X##L
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<float>
#define REAL(X) X##f
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<double>
#define REAL(X) X
#include "optimizer.hxx"
#undef real_t
#undef REAL

#define real_t XReal<long double>
#define REAL(X) X##L
#include "optimizer.hxx"
#undef real_t
#undef REAL

        }

    }

}


