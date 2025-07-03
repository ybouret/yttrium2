
//! \file

#ifndef Y_Cameo_Selector_Included
#define Y_Cameo_Selector_Included 1

#include "y/type/args.hpp"
#include "y/apex/number.hpp"
#include "y/type/conversion.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        //! select matching API
        template <
        typename T,
        template <typename> class DirectAPI,
        template <typename> class AProxyAPI,
        template <typename> class FPointAPI
        >
        struct Select
        {
            Y_Args_Expose(T,Type);
            static const bool IsApNumber = Y_Is_SuperSubClass_Strict(Apex::Number,MutableType);
            static const bool IsIntegral = TypeTraits<MutableType>::IsIntegral;
            typedef typename Alternative<IsApNumber,DirectAPI<T>,IsIntegral,AProxyAPI<T>,FPointAPI<T>> ::Type API;
        };
    }

}

#endif
