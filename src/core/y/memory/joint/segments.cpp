

#include "y/memory/joint/segments.hpp"
#include "y/memory/allocator/dyadic.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Joint
        {

            namespace
            {
                static inline unsigned computeTableShift() noexcept
                {
                    const unsigned numSlots = Segment::MaxDataShift - Segment::MinDataShift + 1;
                    unsigned       theShift = 0;
                    const size_t   numBytes = NextPowerOfTwo(numSlots * sizeof(Segments::Slot), theShift);
                    (void)numBytes;
                    std::cerr << "numSlots=" << numSlots << " => " << numBytes << " = 2^" << theShift << std::endl;
                    return theShift;
                }
            }

            Segments:: Segments() :
            table(0),
            tableShift( computeTableShift() ),
            dyadic( Dyadic::Instance() )
            {
                Coerce(table) = static_cast<Slot*>( dyadic.acquireDyadic(tableShift) )-Segment::MinDataShift;
            }


            Segments:: ~Segments() noexcept
            {
#if 0
                for(unsigned bs=Segment::MinDataShift;bs<=Segment::MaxDataShift;++bs)
                {
                    Slot &slot = table[bs];
                    while(slot.size)
                        unload( slot.popTail() );
                }
#endif
                dyadic.releaseDyadic(table+Segment::MinDataShift,tableShift);
                Coerce(table)      = 0;
                Coerce(tableShift) = 0;
            }

            void Segments:: unload(Segment * const segment) noexcept
            {

                assert(0!=segment);
                assert(0==segment->next);
                assert(0==segment->prev);
                assert(Dyadic::Exists());

                // check errors ?
                Segment::Param &param = segment->param;
                dyadic.releaseDyadic(segment,param.shift);
            }


            void Segments:: release(void * const blockAddr) noexcept
            {
                assert(0!=blockAddr);
                Segment * const segment = Segment::Release(blockAddr);
                assert(0!=segment);
                if( segment->isEmpty() )
                {
                    
                }
            }

 

        }

    }

}


