
//! \file

#ifndef Y_MKL_API_Selector_Included
#define Y_MKL_API_Selector_Included 1

#include "y/type/traits.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{
    namespace MKL
    {
        //! named API type
        enum API_Type
        {
            API_Integral, //!< char,...,uint64_t
            API_Floating, //!< float|double|long double
            API_MustCall  //!< .meth()
        };

        typedef IntToType<API_Integral> IntegralAPI; //!< alias
        typedef IntToType<API_Floating> FloatingAPI; //!< alias
        typedef IntToType<API_MustCall> MustCallAPI; //!< alias

        //! select matching API
        template <typename T>
        struct API_Select
        {
            static const bool IsIntegral = TypeTraits<T>::IsIntegral;         //!< alias
            static const bool IsFloating = TypeTraits<T>::IsIsoFloatingPoint; //!< alias

            //! compute selected type
            typedef typename Alternative<IsIntegral, IntegralAPI, IsFloating, FloatingAPI, MustCallAPI>::Type Choice;
        };

    }

}

#endif

