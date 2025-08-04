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
            static const unsigned Table[256]; //!< precomputed table

            //! \return sum of bits in each byte of block
            static size_t         Block(const void * const, const size_t) noexcept;
        };
    }

    //! \param args integral type \return sum of bits in args
    template <typename T> inline
    size_t BitsIn(const T &args) noexcept
    {
        return Calculus::BitsIn::Block(&args,sizeof(T));
    }


}


#endif

