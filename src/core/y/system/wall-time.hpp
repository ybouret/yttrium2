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

            static uint64_t Ticks();
            long double operator()(const uint64_t) const noexcept;
            long double since(const uint64_t start) const;

        private:
            Y_Disable_Copy_And_Assign(WallTime);
            Code * const code;
        };
    }
}

#endif


