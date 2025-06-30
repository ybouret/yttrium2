
//! \file

#ifndef Y_Type_IsSigned_Included
#define Y_Type_IsSigned_Included 1

namespace Yttrium
{

    //! finding static signed type
    template <typename T> struct IsSigned
    {
        static const T n = T(-1);        //!< should be negative
        static const T p = T(1);         //!< positive
        static const bool Value = (n<p); //!< result
    };
}


#endif


