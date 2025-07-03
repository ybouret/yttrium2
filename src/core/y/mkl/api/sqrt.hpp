
//! \file

#ifndef Y_MKL_Sqrt_Included
#define Y_MKL_Sqrt_Included 1

#include "y/type/args.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            template <typename T,bool> struct Sqrt;

            template <typename T> struct Sqrt<T,true>
            {
                static inline T Of(const T x) noexcept { return std::sqrt(x); }
            };

            template <typename T> struct Sqrt<T,false>
            {
                static inline T Of(const T &x) { return x.sqrt(); }
            };
        }

        template <typename T> struct Sqrt
        {
            Y_Args_Declare(T,Type);
            static inline Type Of(ParamType x)
            {
                return Kernel::Sqrt<T,TypeTraits<MutableType>::IsIsoFloatingPoint>::Of(x);
            }
        };


    }

}

#endif

