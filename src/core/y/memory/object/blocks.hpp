
//! \file

#ifndef Y_Memory_Blocks_Included
#define Y_Memory_Blocks_Included 1

#include "y/memory/object/arena.hpp"
#include "y/core/linked/list.hpp"
#include "y/core/linked/pool.hpp"

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
                static const char * const CallSign;
                static const unsigned TableSizeLn2 = 5;
                static const size_t   TableSize = size_t(1) << TableSizeLn2;
                static const size_t   TableMask = TableSize - 1;
                typedef Core::ListOf<Arena> Slot;

                class Knot
                {
                public:
                    typedef Core::PoolOf<Knot> Pool;
                    Knot(const size_t blockSize, const size_t pageBytes);
                    ~Knot() noexcept;
                    Arena arena;
                    Knot * next;
                private:
                    Y_Disable_Copy_And_Assign(Knot);
                };

                explicit Blocks(const size_t userPageBytes);
                virtual ~Blocks() noexcept;

                void * acquire(const size_t blockSize);
                void   release(void * const blockAddr, const size_t blockSize) noexcept;

            private:
                Y_Disable_Copy_And_Assign(Blocks);
                Arena *        newAcquiring(const size_t blockSize);
                Arena *        search(const size_t blockSize) noexcept;
                Arena *        acquiring;
                Arena *        releasing;
                const unsigned pageShift;
                const size_t   pageBytes;
                Knot::Pool     kpool;
                Arena          knots;
                Slot           table[TableSize];
            };
        }
    }

}

#endif

