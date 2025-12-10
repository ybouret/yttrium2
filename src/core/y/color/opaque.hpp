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
            template <typename T>
            struct OpaqueFP
            {
                static const T Value;
            };

            template <typename T>
            const T OpaqueFP<T>::Value = T(1);

            template <typename T>
            struct OpaqueIP
            {
                static const T Value = IntegerFor<T>::Maximum;
            };
            

        }

        template <typename T>
        struct Opaque
        {
            static const bool UseFP = TypeTraits<T>::IsIsoFloatingPoint;
            typedef typename Pick<UseFP, Privy::OpaqueFP<T>, Privy::OpaqueIP<T> >::Type API;
            static const T Value;
        };

        template <typename T>
        const T Opaque<T>:: Value = Opaque<T>::API::Value;


    }

}

#endif // !Y_Color_Opaque_Included

