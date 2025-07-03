
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

            //! sqrt for float,double, long double
            template <typename T> struct Sqrt<T,true>
            {
                //! \param x value \return sqrt(x)
                static inline T Of(const T x) noexcept { return std::sqrt(x); }
            };

            //! sqrt for class
            template <typename T> struct Sqrt<T,false>
            {
                //! \param x value \return x.sqrt()
                static inline T Of(const T &x) { return x.sqrt(); }
            };
        }

        //! sqrt selector for types
        template <typename T> struct Sqrt
        {
            Y_Args_Declare(T,Type); //!< aliases

            //! \param x value \return |x|
            static inline Type Of(ParamType x)
            {
                return Kernel::Sqrt<T,TypeTraits<MutableType>::IsIsoFloatingPoint>::Of(x);
            }
        };


    }

}

#endif

