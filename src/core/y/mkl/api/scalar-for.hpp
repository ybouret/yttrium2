
//! \file

#ifndef Y_MKL_ScalarFor_Included
#define Y_MKL_ScalarFor_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    template <typename> class Complex;
    template <typename> class V2D;
    template <typename> class V3D;
    template <typename> class V4D;


    namespace MKL
    {

        template <typename T> struct ScalarFor;

        //! select scalar for complex
        template <typename T>
        struct ScalarFor< Complex<T> >
        {
            typedef T Type; //!< alias
        };

        //! select scalar for complex
        template <typename T>
        struct ScalarFor< V2D<T> >
        {
            typedef T Type; //!< alias
        };


        //! select scalar for complex
        template <typename T>
        struct ScalarFor< V3D<T> >
        {
            typedef T Type; //!< alias
        };

        //! select scalar for complex
        template <typename T>
        struct ScalarFor< V4D<T> >
        {
            typedef T Type; //!< alias
        };


        //! select scalar for scalar
        template <typename T>
        struct ScalarFor
        {
            typedef T Type; //!< alias
        };


        //! testing is type is scalar
        template <typename T>
        struct IsScalarType
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

