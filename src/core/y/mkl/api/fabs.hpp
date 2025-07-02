

//! \file

#ifndef Y_MKL_Fabs_Included
#define Y_MKL_Fabs_Included 1

#include "y/mkl/api/scalar-for.hpp"

namespace Yttrium
{
    namespace MKL
    {

        // IsoFloatingPoint : std::fabs
        // XReal<...>  x.abs(), todo for complex

        namespace Kernel
        {
            template <typename T,bool> struct Fabs;

            template <typename T> struct Fabs<T,true>
            {
                static inline T Of(const T x) noexcept { return std::fabs(x); }
            };

            template <typename T> struct Fabs<T,false>
            {
                static inline
                typename ScalarFor<T>::Type Of(const T &x) { return x.abs(); }
            };
        }

        template <typename T> struct Fabs
        {
            Y_Args_Declare(T,Type);
            typedef typename ScalarFor<MutableType>::Type ScalarType;
            static inline ScalarType Of(ParamType x) {
                return Kernel::Fabs<T,TypeTraits<MutableType>::IsIsoFloatingPoint>(x);
            }
        };


    }

}

#endif

