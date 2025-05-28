
//! \file

#ifndef Y_Memory_Blocks_Included
#define Y_Memory_Blocks_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Object
        {
            class Book;

            class Blocks
            {
            public:
                class Code;

                explicit Blocks(const size_t userPageSize);
                virtual ~Blocks() noexcept;

                Book &book;
            private:
                Y_Disable_Copy_And_Assign(Blocks);
                const unsigned pageShift;
                const size_t   pageBytes;
                const unsigned codeShift;
                const size_t   codeBytes;
                Code *         code;

            };
        }
    }

}

#endif

