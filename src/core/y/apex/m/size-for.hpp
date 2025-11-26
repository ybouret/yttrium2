

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

        //! compute words to hold bits
        template <typename T>
        struct SizeFor
        {
            static const unsigned BitsPerWord = 8*sizeof(T); //!< alias

            //! \param numBits computed bits \return words to hold numBits
            static inline size_t  From(const size_t numBits) noexcept
            {
                return Alignment::On<BitsPerWord>::Ceil(numBits) / BitsPerWord;
            }
        };
    }
}

#endif // !Y_Apex_Size_For_Included

