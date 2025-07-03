
//! \file

#ifndef Y_MKL_ScalarFor_Included
#define Y_MKL_ScalarFor_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    template <typename> class Complex;
    
    namespace MKL
    {

        template <typename T> struct ScalarFor;

        template <typename T>
        struct ScalarFor< Complex<T> >
        {
            typedef T Type;
        };

        template <typename T>
        struct ScalarFor
        {
            typedef T Type;
        };


        template <typename T>
        struct IsScalarType
        {
            Y_Args_Expose(T,Type);
            typedef typename ScalarFor<MutableType>::Type ScalarType;
            enum { Value = IsSameType<MutableType,ScalarType>::Value };
        };
    }

}

#endif

