
//! \file

#ifndef Y_Memory_Limits_Included
#define Y_Memory_Limits_Included 1

#include "y/calculus/base2.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //! Common static limits
        struct Limits
        {
            static const size_t   MinBlockBytes    = 128;                               //!< for Object::Chunk and Pages
            static const unsigned MinBlockShift    = IntegerLog2<MinBlockBytes>::Value; //!< log2(MinBlockBytes)
            static const size_t   MaxBlockBytes    = Base2<size_t>::MaxBytes;           //!< largest power of two
            static const unsigned MaxBlockShift    = Base2<size_t>::MaxShift;           //!< largest power of two exponent
        };
    }

}

#endif

