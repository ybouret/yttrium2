//! \file

#ifndef Y_MKL_Adaptor_Included
#define Y_MKL_Adaptor_Included 1

#include "y/type/conversion.hpp"
#include "y/type/traits.hpp"
#include <iostream>

namespace Yttrium
{
    namespace MKL
    {
        namespace Kernel
        {
            template <typename T, typename U, bool>
            struct Adaptor;

            template <typename T, typename U>
            struct Adaptor<T,U,true>
            {
                typedef const T &                         ReturnType;
                static inline ReturnType Get(const U & u)
                {
                    return u;
                }
            };

            template <typename T, typename U>
            struct Adaptor<T,U,false>
            {
                typedef   T ReturnType;
                static inline ReturnType Get(const U & u)
                {
                    return (T)u;
                }
            };


        }

        template <typename T, typename U>
        struct Adaptor
        {
            static const bool IsDerived = Y_Is_SuperSubClass(T,U);
            typedef  Kernel::Adaptor<T,U,IsDerived> API;
        };

        template <typename T, typename U> inline
        typename Adaptor<T,U>::API::ReturnType AdaptedTo(const TypeToType<T> &, const U & u )
        {
            return  Adaptor<T,U>::API::Get(u);
        }



    }

}

#endif
