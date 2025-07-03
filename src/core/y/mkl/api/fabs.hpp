

//! \file

#ifndef Y_MKL_Fabs_Included
#define Y_MKL_Fabs_Included 1

#include "y/mkl/api/scalar-for.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {

        // IsoFloatingPoint : std::fabs
        // XReal<...>  x.abs(), todo for complex

        namespace Kernel
        {
            template <typename T,bool> struct Fabs;

            //! fabs for float,double,long double
            template <typename T> struct Fabs<T,true>
            {
                //! \param x value \return std::fabs(x)
                static inline T Of(const T x) noexcept { return std::fabs(x); }
            };

            //! fabs for classes
            template <typename T> struct Fabs<T,false>
            {
                //! \param x value \return x.abs()
                static inline typename ScalarFor<T>::Type Of(const T &x) { return x.abs(); }
            };
        }

        //! wrapper to select fabs()
        template <typename T> struct Fabs
        {
            Y_Args_Declare(T,Type);                                   //!< aliases
            typedef typename ScalarFor<MutableType>::Type ScalarType; //!< alias

            //! \param x value \return |x|
            static inline ScalarType Of(ParamType x)
            {
                return Kernel::Fabs<T,TypeTraits<MutableType>::IsIsoFloatingPoint>::Of(x);
            }
        };


    }

}

#endif

