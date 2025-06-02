
//! \file


#ifndef Y_Check_Usual_Included
#define Y_Check_Usual_Included 1

#include "y/system/compiler.hpp"
#include "y/system/compiler.hpp"
#include <cassert>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! Test that a memory block is valid
    /**
     \param blockAddr address of the block
     \param blockSize size of the block
     \return !(0==blockAddr && blockSize>0)
     */
    //
    //__________________________________________________________________________
    bool Good(const void * const blockAddr,
              const size_t       blockSize) noexcept;

    //__________________________________________________________________________
    //
    //
    //! helper to document assertions
    /**
     \return false
     */
    //
    //__________________________________________________________________________
    bool Die(const char * const) noexcept;

#if !defined(NDEBUG)
    //! insert optional debug code
#define Y_Debug(CODE) CODE
#else
#define Y_Debug(CODE)
#endif

}

#endif

