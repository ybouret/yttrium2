//! \file
//!
#ifndef Y_Calculus_BitsIn_Included
#define Y_Calculus_BitsIn_Included 1

#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        //______________________________________________________________________
        //
        //
        //
        //! low-level BitsIn computation
        //
        //
        //______________________________________________________________________
        struct BitsIn
        {
            static const unsigned Table[256];
            static size_t         Block(const void * const, const size_t) noexcept;
        };
    }

    template <typename T> inline
    size_t BitsIn(const T &args) noexcept
    {
        return Calculus::BitsIn::Block(&args,sizeof(T));
    }


}


#endif

