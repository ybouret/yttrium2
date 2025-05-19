
//! \file


#ifndef Y_Check_Usual_Included
#define Y_Check_Usual_Included 1

#include "y/system/compiler.hpp"
#include "y/system/types.hpp"
#include <cassert>

namespace Yttrium
{
    bool Good(const void * const blockAddr,
              const size_t       blockSize) noexcept;

    bool Die(const char * const) noexcept;
}

#endif

