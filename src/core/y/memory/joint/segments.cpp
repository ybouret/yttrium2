

#include "y/memory/joint/segments.hpp"
#include "y/memory/object/book.hpp"
#include "y/memory/object/factory.hpp"
#include "y/core/utils.hpp"
#include "y/xml/syntax.hpp"

#include "y/system/error.hpp"
#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {
        namespace Joint
        {

            Segments:: Slot:: Slot() noexcept : ListType(), alreadyEmpty(0)
            {
            }

            Segments:: Slot:: ~Slot() noexcept
            {
                alreadyEmpty = 0;
            }

            void  Segments:: Slot:: show(std::ostream &os,size_t indent) const
            {
                for(const Segment *s=head;s;s=s->next)
                {
                    s->display(XML::Indent(os,indent) << '@' << (const void *)s << ' ');
                }
            }


            const unsigned Segments:: MinShift = Object::Factory::DEFAULT_PAGE_SHIFT;

            namespace
            {
                static inline unsigned computeTableShift() noexcept
                {
                    const unsigned numSlots = Segments::MaxShift- Segments::MinShift + 1;
                    unsigned       theShift = 0;
                    const size_t   numBytes = NextPowerOfTwo(numSlots * sizeof(Segments::Slot), theShift);
                    (void)numBytes;
                    //std::cerr << "numSlots=" << numSlots << " => " << numBytes << " = 2^" << theShift << std::endl;
                    return theShift;
                }
            }

            Segments:: Segments() :
            table(0),
            lastSlot(0),
            tableShift( computeTableShift() ),
            book( Object::Book::Instance() )
            {
                Coerce(table) = static_cast<Slot*>( book.query(tableShift) )-MinShift;
                for(unsigned bs=MinShift;bs<=MaxShift;++bs)
                {
                    new (table+bs) Slot();
                }
                Coerce(lastSlot) = table+ (MaxShift+1);
            }


            Segments:: ~Segments() noexcept
            {
                for(unsigned bs=MaxShift;bs>=MinShift;--bs)
                {
                    Slot &slot = table[bs];
                    while(slot.size)
                        unload( slot.popTail() );
                    slot.~Slot();
                }
                book.store(tableShift, table+MinShift);
                Coerce(table)      = 0;
                Coerce(tableShift) = 0;
            }

            void Segments:: unload(Segment * const segment) noexcept
            {

                assert(0!=segment);
                assert(0==segment->next);
                assert(0==segment->prev);

                assert( Segment::IsValid(segment) );
                
                //--------------------------------------------------------------
                // check errors
                //--------------------------------------------------------------
                if(!segment->isEmpty())
                    segment->display(std::cerr << "*** " << Segment::CallSign << "[" << std::setw(6) << segment->param.bytes << "] : ");

                //--------------------------------------------------------------
                // return to book pages
                //--------------------------------------------------------------
                book.store(segment->param.shift,segment);
            }


            void Segments:: release(void * const blockAddr, const size_t blockSize) noexcept
            {
                assert(0!=blockAddr);
                Segment * const segment = Segment::Release(blockAddr,blockSize); assert(0!=segment);
                if(segment->isEmpty())
                {
                    Slot &          slot    = table[segment->param.shift]; assert(slot.owns(segment));
                    Segment * const another = slot.alreadyEmpty;
                    if(another)
                    {
                        assert(slot.size>=2);
                        assert(another->isEmpty());

                        if(another<segment)
                        {
                            // keep another
                            unload( slot.pop(segment) );
                        }
                        else
                        {
                            // keep segment
                            unload( slot.pop(another) );
                            slot.alreadyEmpty = segment;
                        }
                    }
                    else
                    {
                        assert(slot.size>=1);
                        slot.alreadyEmpty = segment;
                    }
                    assert(slot.size>0);
                }

            }

            void * Segments:: acquire(size_t &blockSize)
            {
                const unsigned shift = MaxOf(Segment::ShiftFor(blockSize),MinShift);
                assert(shift>=MinShift);
                assert(shift<=MaxShift);

                // look for accepting slot with big enough shift
                Slot * const       primary = &table[shift];
                {
                    const Slot * const end = lastSlot;
                    for(Slot *slot = primary; slot < end; ++slot)
                    {
                        for(Segment *segment=slot->head;segment;segment=segment->next)
                        {
                            assert(segment->param.maxSize>=blockSize);
                            void * const addr = segment->acquire(blockSize);
                            if(0!=addr)
                            {
                                if(segment==slot->alreadyEmpty)
                                    slot->alreadyEmpty = 0;
                                
                                return addr;
                            }
                        }
                    }
                }

                // need to create a new slot in primary
                assert(0== primary->alreadyEmpty);
                try
                {
                    Segment * const segment = primary->insertOderedByAddresses( Segment::Format( book.query(shift), shift) );
                    assert(0!=segment);
                    assert(segment->param.maxSize>=blockSize);
                    assert(segment->head->used==0);
                    assert(segment->head->size==segment->param.maxSize);
                    void * const addr = segment->acquire(blockSize);
                    assert(0!=addr);
                    return addr;
                }
                catch(...)
                {
                    blockSize = 0;
                    throw;
                }

            }

            uint32_t Segments:: crc32() const noexcept
            {
                uint32_t crc = 0;
                for(unsigned bs=MinShift;bs<=MaxShift;++bs)
                {
                    const Slot &slot = table[bs];
                    for(const Segment *seg=slot.head;seg;seg=seg->next)
                    {
                        crc = seg->crc32(crc);
                    }
                }
                return crc;
            }

            const Segments:: Slot & Segments:: operator[](const unsigned shift) const noexcept
            {
                assert(shift>=MinShift);
                assert(shift<=MaxShift);
                return table[shift];
            }


        }

    }

}


