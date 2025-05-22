
//! \file

#ifndef Y_Calculus_Base2_Included
#define Y_Calculus_Base2_Included 1

#include "y/type/ints.hpp"

namespace Yttrium
{
    template <typename T>
    struct Base2
    {
        typedef T             Type;
        static const Type     One        = 1;
        static const unsigned Size       = sizeof(Type);
        static const unsigned Bits       = Size << 3;
        static const bool     SignedType = IsSigned<T>::Value;
        static const unsigned MaxShift   = SignedType ? (Bits-2) : (Bits-1);
        static const Type     MaxValue   = One << MaxShift;
    };

    template <typename T>
    inline bool IsPowerOfTwo(const T x) noexcept
    {
        return x && (!(x & (x - Base2<T>::One)));
    }

}

#endif
