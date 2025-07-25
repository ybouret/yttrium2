

//! \file

#ifndef Y_MKL_Vectorial_Included
#define Y_MKL_Vectorial_Included 1

#include "y/mkl/api/scalar.hpp"

namespace Yttrium
{

    namespace MKL
    {
        //! testing is type is vectorial
        template <typename T>
        struct IsVectorial
        {
            Y_Args_Expose(T,Type);                                    //!< aliases
            typedef typename ScalarFor<MutableType>::Type ScalarType; //!< alias
            enum
            {
                Value = ! IsSameType<MutableType,ScalarType>::Value //!< true iff not scalar
            };
        };
    }

}

#endif
