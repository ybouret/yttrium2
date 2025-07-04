
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

        //______________________________________________________________________
        //
        //
        //
        //! select matching API according to type
        //
        //
        //______________________________________________________________________
        template <
        typename T,
        class DirectAPI,
        class AProxyAPI,
        class FPointAPI
        >
        struct Select
        {
            Y_Args_Expose(T,Type); //!< aliases
            static const bool IsApNumber = Y_Is_SuperSubClass_Strict(Apex::Number,MutableType); //!< ap[n|z|q]
            static const bool IsIntegral = TypeTraits<MutableType>::IsIntegral;                 //!< integral type

            //! default to floating point
            typedef typename Alternative<IsApNumber,DirectAPI,IsIntegral,AProxyAPI,FPointAPI>::Type API;
        };
    }

}

#endif
