#include "y/memory/object/blocks.hpp"
#include "y/memory/object/book.hpp"
#include "y/memory/object/arena.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/core/utils.hpp"
#include "y/type/destruct.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/align.hpp"
#include "y/check/static.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        namespace Object
        {

            Blocks:: Knot:: Knot(const size_t blockSize, const size_t pageBytes) :
            arena(blockSize,pageBytes),
            next(0)
            {
            }

            Blocks:: Knot:: ~Knot() noexcept
            {

            }


            Blocks:: Blocks(const size_t userPageBytes) :
            acquiring(0),
            releasing(0),
            pageShift(0),
            pageBytes( NextPowerOfTwo( Clamp(Book::MinPageBytes,userPageBytes,Book::MaxPageBytes), Coerce(pageShift))),
            kpool(),
            knots(sizeof(Knot),pageBytes),
            table()
            {
                std::cerr << "sizeof(table)=" << sizeof(table) << std::endl;
            }

            Blocks:: ~Blocks() noexcept
            {
#if 0
                for(size_t i=0;i<TableSize;++i)
                {
                    Slot &slot = table[i];
                    Stealth::Zero(&slot,sizeof(Slot));
                }
#endif
                Y_Memory_BZero(table);
                while(kpool.size) knots.release( Destructed(kpool.query()) );

            }


            Arena * Blocks:: newAcquiring(const size_t blockSize)
            {
                assert(blockSize>0);
                void * const knotAddr = knots.acquire();
                try {
                    Arena * const arena = & kpool.store( new (knotAddr) Knot(blockSize,pageBytes) )->arena;
                    return (acquiring = table[ arena->hkey & TableMask ].pushHead(arena));
                }
                catch(...)
                {
                    knots.release(knotAddr);
                    throw;
                }
            }


            Arena * Blocks:: search(const size_t blockSize) noexcept
            {
                assert(blockSize>0);
                Slot &slot = table[ Arena::Hash(blockSize) & TableMask ];
                for(Arena *a=slot.head;a;a=a->next)
                {
                    if(blockSize==a->blockSize) return slot.moveToFront(a);
                }
                return 0;
            }


            void * Blocks:: acquire(const size_t blockSize)
            {
                assert(blockSize>0);
                if(acquiring && blockSize==acquiring->blockSize) return acquiring->acquire(); // cached
                if( 0!=(acquiring = search(blockSize) ) )        return acquiring->acquire(); // existing
                return newAcquiring(blockSize)->acquire();                                    // new
            }


            void Blocks:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                assert(0!=blockAddr);
                assert(0!=blockSize);
                if(releasing && blockSize==releasing->blockSize) { return releasing->release(blockAddr); }
                releasing = search(blockSize);
                if(!releasing) {
                    Libc::Error::Critical(EINVAL, "address/blockSize not allocated by Memory::Object::Blocks");
                }
                return releasing->release(blockAddr);
            }



        }
    }
}

