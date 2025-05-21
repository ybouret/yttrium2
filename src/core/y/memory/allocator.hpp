
//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Allocator
        {
        public:
            explicit Allocator() noexcept;
        protected:
            virtual ~Allocator() noexcept;

            static void AlignBlockSize(size_t &blockSize);

        private:
            Y_Disable_Copy_And_Assign(Allocator);
        };
    }

}

#endif
