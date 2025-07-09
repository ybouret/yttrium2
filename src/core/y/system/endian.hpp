

//! \file

#ifndef Y_System_Endian_Included
#define Y_System_Endian_Included 1


#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"

namespace Yttrium
{
    //! RunTime Endian detecting
    struct Endian
    {
        static bool         Little()        noexcept; //!< \return LE architecture
        static bool         Big()           noexcept; //!< \return BE architecture
        static const char * HumanReadable() noexcept; //!< \return Litte/Big endina
    };
}

#endif
