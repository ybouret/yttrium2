
//! \file

#ifndef Y_Apex_Types_Included
#define Y_Apex_Types_Included 1

#include "y/calculus/bits-for.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Apex
    {
        typedef uint64_t natural_t; //!< alias to unsigned
        typedef int64_t  integer_t; //!< alias to signed

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

