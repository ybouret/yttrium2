
//! \file

#ifndef Y_Memory_Arena_Included
#define Y_Memory_Arena_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {


        class Arena
        {
        public:
            Arena(const size_t userBlockSize,
                  const size_t userPageBytes);
            ~Arena() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Arena);
        };
    }

}

#endif

