
//! \file

#ifndef Y_Memory_Align_Included
#define Y_Memory_Align_Included 1

#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! helper for memory alignment
        //
        //
        //______________________________________________________________________
        struct Align
        {
            typedef Alignment::On<16> Compute;                                //!< alias
            static const size_t       MaxBlockSize = Compute::Inner::Maximum; //!< alias
            static const size_t       MinBlockSize = Compute::Inner::Byte;    //!< alias
        };

    }

}

#endif

