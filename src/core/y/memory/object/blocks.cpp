#include "y/memory/object/blocks.hpp"
#include "y/memory/object/book.hpp"
#include "y/core/utils.hpp"
#include "y/type/destruct.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include "y/decimal.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        namespace Object
        {

            const char * const Blocks:: CallSign = "Memory::Object::Blocks";

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
                assert(blockSize>0);
                if(releasing && blockSize==releasing->blockSize) { return releasing->release(blockAddr); }
                releasing = search(blockSize);
                if(0==releasing)
                {
                    Libc::Error::Critical(EINVAL, "@%p+%s not allocated by %s", blockAddr, Decimal(blockSize).c_str(), CallSign);
                    return; // to avoid report in code analysis
                }

                return releasing->release(blockAddr);
            }



        }
    }
}

