
//! \file

#ifndef Y_Memory_Align_Included
#define Y_Memory_Align_Included 1

#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Memory
    {

        struct Align
        {
            typedef Alignment::On<16> Compute;
            static const size_t       MaxBlockSize = Compute::Inner::Maximum;
            static const size_t       MinBlockSize = Compute::Inner::Byte;
        };

    }

}

#endif

