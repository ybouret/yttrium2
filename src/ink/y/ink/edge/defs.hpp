
//! \file

#ifndef Y_Ink_Edge_Defs_Included
#define Y_Ink_Edge_Defs_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! Edge properties
        struct EdgeIs
        {
            static const uint8_t Absent = 0x00; //!< alias
            static const uint8_t Feeble = 0x40; //!< alias
            static const uint8_t Strong = 0x80; //!< alias

            //! normalize flag value
            /**
             \param flag input flage
             \return acceptable value depending on flag
             */
            static   uint8_t NamedFrom(const uint8_t flag) noexcept;

        };
    }

}

#endif // !Y_Ink_Edge_Defs_Included

