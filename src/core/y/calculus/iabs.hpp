
//! \file

#ifndef Y_Calculus_IntegerAbs_Included
#define Y_Calculus_IntegerAbs_Included 1

#include "y/type/ints.hpp"
#include "y/type/is-signed.hpp"

namespace Yttrium
{

    namespace Calculus
    {
        //! integer square root algorithm
        struct IntegerAbs
        {

            //! unsigned \param s argument \return isqrt
            template <typename T> static inline
            T Compute(const T s, const IntToType<false> &) noexcept
            {
                return s;
            }

            //! signed \param s argument \return isqrt
            template <typename T> static inline
            T Compute(const T s, const IntToType<true> &) noexcept
            {
                return s < T(0) ? -s : s;
            }

        };


    }

    //! integer square root \param s integral value \return isqrt
    template <typename T> inline
    T IntegerAbs(const T s) noexcept
    {
        static const IntToType< IsSigned<T>::Value > Choice = {};
        return Calculus::IntegerAbs::Compute(s,Choice);
    }

}

#endif


