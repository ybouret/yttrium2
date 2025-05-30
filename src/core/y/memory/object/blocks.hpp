
//! \file

#ifndef Y_Memory_Blocks_Included
#define Y_Memory_Blocks_Included 1

#include "y/memory/object/arena.hpp"
#include "y/core/linked/list.hpp"

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
                static const unsigned TableSizeLn2 = 5;
                static const size_t   TableSize = size_t(1) << TableSizeLn2;
                static const size_t   TableMask = TableSize - 1;
                typedef Core::ListOf<Arena> Slot;

                explicit Blocks(const size_t userPageBytes);
                virtual ~Blocks() noexcept;

                //void * acquire(const size_t blockSize);
                //void   release(void * const blockAddr, const size_t blockSize) noexcept;

            private:
                Y_Disable_Copy_And_Assign(Blocks);
                const unsigned pageShift;
                const size_t   pageBytes;
                Slot           table[TableSize];

            };
        }
    }

}

#endif

