

//! \file

#ifndef Y_Apex_Size_For_Included
#define Y_Apex_Size_For_Included 1

#include "y/apex/types.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Apex
    {
        
        template <typename T>
        struct SizeFor
        {
            static const unsigned Bits = 8*sizeof(T);
            static inline size_t  From(const size_t numBits) noexcept
            {
                return Alignment::On<Bits>::Ceil(numBits) / Bits;
            }
        };
    }
}

#endif

