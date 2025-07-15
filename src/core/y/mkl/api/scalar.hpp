
//! \file

#ifndef Y_MKL_Scalar_Included
#define Y_MKL_Scalar_Included 1

#include "y/mkl/api/scalar-for.hpp"

namespace Yttrium
{

    namespace MKL
    {

        //! testing is type is scalar
        template <typename T>
        struct IsScalar
        {
            Y_Args_Expose(T,Type);                                    //!< aliases
            typedef typename ScalarFor<MutableType>::Type ScalarType; //!< alias
            enum
            {
                Value = IsSameType<MutableType,ScalarType>::Value //!< true iff scalar
            };
        };
    }

}

#endif
