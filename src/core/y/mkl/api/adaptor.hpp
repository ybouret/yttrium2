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

            //! adaptor for derived types
            template <typename T, typename U>
            struct Adaptor<T,U,true>
            {
                typedef const T & ReturnType; //!< alias

                //! \param u derived type \return its reference
                static inline ReturnType Get(const U & u)
                {
                    return u;
                }
            };

            //! adaptor for not derived class
            template <typename T, typename U>
            struct Adaptor<T,U,false>
            {
                typedef   T ReturnType; //!< alias

                //! \param u data  \return its copy
                static inline ReturnType Get(const U & u)
                {
                    return (T)u;
                }
            };


        }

        //! adaptor selection depending on relationship
        template <typename T, typename U>
        struct Adaptor
        {
            static const bool IsDerived = Y_Is_SuperSubClass(T,U); //!< alias
            typedef  Kernel::Adaptor<T,U,IsDerived> API;           //!< selected API
        };

        //! \param u data \return adapted return type to T
        template <typename T, typename U> inline
        typename Adaptor<T,U>::API::ReturnType AdaptedTo(const TypeToType<T> &, const U & u )
        {
            return  Adaptor<T,U>::API::Get(u);
        }



    }

}

#endif // !Y_MKL_Adaptor_Included
