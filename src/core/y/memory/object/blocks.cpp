#include "y/memory/object/blocks.hpp"
#include "y/memory/object/ledger.hpp"
#include "y/memory/object/metrics.hpp"

#include "y/core/utils.hpp"
#include "y/type/destruct.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include "y/decimal.hpp"
#include "y/xml/attribute.hpp"
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


            Blocks:: Blocks() :
            acquiring(0),
            releasing(0),
            pageShift(0),
            pageBytes( NextPowerOfTwo( Clamp(Ledger::MinPageBytes,Metrics::DefaultPageBytes,Ledger::MaxPageBytes), Coerce(pageShift))),
            kpool(),
            knots(sizeof(Knot),pageBytes),
            table()
            {
            }

            void Blocks:: sort() noexcept
            {
                
            }


            Blocks:: ~Blocks() noexcept
            {
                //Y_Memory_BZero(table);
                for(size_t i=0;i<TableSize;++i)
                {
                    Slot &slot = table[i];
                    Coerce(slot.size) = 0;
                    slot.head = 0;
                    slot.tail = 0;
                }
                while(kpool.size)
                    knots.release( Destructed(kpool.query()) );
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


            Arena & Blocks:: getArenaFor(const size_t blockSize)
            {
                assert(blockSize>0);
                if(acquiring && blockSize==acquiring->blockSize) return *acquiring; // cached
                if( 0!=(acquiring = search(blockSize) ) )        return *acquiring; // existing
                return *newAcquiring(blockSize);                                    // new
            }

            void * Blocks:: acquire(const size_t blockSize)
            {
                assert(blockSize>0);
                return getArenaFor(blockSize).acquire();
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


            const char * Blocks:: callSign() const noexcept { return CallSign; }

            void Blocks:: display(std::ostream &os, size_t indent) const
            {
                initProlog(os,indent);
                os << Attribute("numArena",kpool.size);
                initEpilog(os,true);
            }






        }
    }
}

