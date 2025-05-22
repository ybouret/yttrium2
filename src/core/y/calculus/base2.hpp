
//! \file

#ifndef Y_Calculus_Base2_Included
#define Y_Calculus_Base2_Included 1

#include "y/type/ints.hpp"
#include <cassert>

namespace Yttrium
{
    //! Metrics for Base2 operations
    template <typename T>
    struct Base2
    {
        typedef T             Type;                                          //!< alias
        static const Type     One        = 1;                                //!< alias
        static const unsigned Size       = sizeof(Type);                     //!< in bytes
        static const unsigned Bits       = Size << 3;                        //!< bit count
        static const bool     SignedType = IsSigned<T>::Value;               //!< alias
        static const unsigned MaxShift   = SignedType ? (Bits-2) : (Bits-1); //!< max shift
        static const Type     MaxValue   = One << MaxShift;                  //!< max value
    };

    //! Test is x is a power of two
    /** \param x integral type \return true if x==2^n */
    template <typename T>
    inline bool IsPowerOfTwo(const T x) noexcept
    {
        return x && (!(x & (x - Base2<T>::One)));
    }

    //! Find next power of two
    /**
     \param x <= Base2<T>::MaxValue
     \return n=2^p>=x
     */
    template <typename T>
    inline T NextPowerOfTwo(const T x) noexcept
    {
        assert( x <= Base2<T>::MaxValue );
        T n = Base2<T>::One;
        while(n<x) n <<= 0x1;
        return n;
    }

}

#endif
