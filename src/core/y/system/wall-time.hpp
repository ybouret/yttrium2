//! \file
//!
#ifndef Y_System_WallTime_Included
#define Y_System_WallTime_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace System
    {
        class WallTime
        {
        public:
            class Code;
            explicit WallTime();
            virtual ~WallTime() noexcept;

        private:
            Y_Disable_Copy_And_Assign(WallTime);
            Code * const code;
        };
    }
}

#endif


