#include "y/memory/small/blocks.hpp"
#include "y/memory/small/ledger.hpp"
#include "y/memory/small/metrics.hpp"

#include "y/core/utils.hpp"
#include "y/type/destruct.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include "y/format/decimal.hpp"
#include "y/xml/attribute.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            const char * const Blocks:: CallSign = "Memory::Small::Blocks";

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

            static inline SignType CompareKnots(const Blocks::Knot *lhs,
                                               const Blocks::Knot *rhs) noexcept
            {
                assert(0!=lhs);
                assert(0!=rhs);
                return Sign::Of(lhs->arena.blockSize,rhs->arena.blockSize);
            }

            void Blocks:: sort() noexcept
            {
                //kpool.sortByIncreasingAddress();
                kpool.sort(CompareKnots);
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
                if(kpool.size<=0)
                {
                    initEpilog(os,true);
                    return;
                }
                initEpilog(os,false);
                ++indent;
                for(const Knot *knot=kpool.head;knot;knot=knot->next)
                {
                    knot->arena.display(std::cerr,indent);
                }
                --indent;
                quit(os,indent);
            }


            bool Blocks:: owns(const void * const addr, size_t &blockSize) const noexcept
            {
                assert(0!=addr);
                for(const Knot *knot=kpool.head;knot;knot=knot->next)
                {
                    const Arena & a = knot->arena;
                    if(a.owns(addr))
                    {
                        blockSize = a.blockSize;
                        return true;
                    }
                }
                return false;
            }




        }
    }
}

