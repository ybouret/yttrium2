//! \file

#ifndef Y_Color_Opaque_Included
#define Y_Color_Opaque_Included

#include "y/type/traits.hpp"
#include "y/type/ints.hpp"
#include "y/type/pick.hpp"

namespace Yttrium
{
    namespace Color
    {
        namespace Privy
        {
            //! Floating Point Opaque value
            template <typename T>
            struct OpaqueFP
            {
                static const T Value; //!< 1
            };

            template <typename T>
            const T OpaqueFP<T>::Value = T(1); //!< instance

            //! Integral Point Opaque Value
            template <typename T>
            struct OpaqueIP
            {
                static const T Value = IntegerFor<T>::Maximum; //!< maximum
            };

        }

        //______________________________________________________________________
        //
        //
        //
        //! opaque value
        //
        //
        //______________________________________________________________________
        template <typename T>
        struct Opaque
        {
            static const bool UseFP = TypeTraits<T>::IsIsoFloatingPoint;                     //!< alias
            typedef typename Pick<UseFP, Privy::OpaqueFP<T>, Privy::OpaqueIP<T> >::Type API; //!< alias

            static const T Value; //!< value for floating point or integral
        };

        template <typename T>
        const T Opaque<T>:: Value = Opaque<T>::API::Value; //!< instance


    }

}

#endif // !Y_Color_Opaque_Included

