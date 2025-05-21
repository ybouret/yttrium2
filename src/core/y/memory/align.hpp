
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
            typedef Alignment::On<16> On;
        };

    }

}

#endif

