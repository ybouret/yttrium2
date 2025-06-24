
#include "y/apex/m/archon.hpp"
#include "y/xml/attribute.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/allocator/quanta.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {


        typedef Core::PoolOf<Memory::Page> SlotType;

        class Archon:: Slot : public SlotType
        {
        public:
            explicit Slot(const unsigned shift) noexcept :
            SlotType(),
            allocated(0),
            bytes( size_t(1) << shift )
            {}
            virtual ~Slot() noexcept {}

            size_t       allocated;
            const size_t bytes;
        private:
            Y_Disable_Copy_And_Assign(Slot);
        };


        void Archon:: display(std::ostream &os,size_t indent) const
        {
            initProlog(os,indent) << Y_XML_Attr(MinShift) << Y_XML_Attr(MaxShift);
            initEpilog(os,false);
            ++indent;
            bool hasData = false;
            for(unsigned i=MinShift;i<=MaxShift;++i)
            {
                const Slot & slot = slots[i];
                if(slot.size||slot.allocated)
                {
                    hasData = true;
                    XML::Indent(os,indent)
                    << "|2^" << std::setw(2) << i << "|"
                    << " available = " << std::setw(6) << slot.size
                    << " allocated = " << std::setw(6) << slot.allocated
                    << std::endl;
                }
            }
            if(!hasData) XML::Indent(os,indent) << "empty cache" << std::endl;
            --indent;
            quit(os,indent);
        }


        void * Archon:: query(const unsigned shift)
        {
            Y_Lock(access);
            if(shift<MinShift||shift>MaxShift) throw Specific::Exception(CallSign,"invalid shift=%u",shift);
            Slot &slot = slots[shift];
            if( slot.size>0 )
            {
                ++slot.allocated;
                return  Memory::Page::Addr(slot.query(),slot.bytes);
            }
            else
            {
                void * const block = quanta.acquireDyadic(shift);
                assert( Memory::Stealth::Are0(block,slot.bytes) );
                ++slot.allocated;
                return block;
            }
        }

        void Archon::store(const unsigned shift, void * const block) noexcept
        {
            Y_Lock(access);
            assert(shift>=MinShift);
            assert(shift<=MaxShift);
            Slot &slot = slots[shift];
            assert(slot.allocated>0);
            slot.store( Memory::Page::Cast(block) );
            --slot.allocated;
        }


        const char * const Archon:: CallSign = "Apex::Archon";
        const unsigned Archon::MinShift;
        const unsigned Archon::MaxShift;

        namespace
        {
            static const size_t ArchonBytes_ = sizeof(Archon::Slot) * Archon::NumShifts;
            void *              ArchonSlots_[ Alignment::WordsGEQ<ArchonBytes_>::Count ];
        }

        Archon:: Archon() :
        slots( static_cast<Slot *>( Y_Memory_BZero(ArchonSlots_)) - MinShift ),
        quanta( Memory::Quanta::Instance() )
        {
            for(unsigned i=MinShift;i<=MaxShift;++i) new (slots+i) Slot(i);
        }

        Archon:: ~Archon() noexcept
        {
            Y_Lock(access);
            for(unsigned i=MaxShift;i>=MinShift;--i)
            {
                Slot &slot = slots[i];
                if(slot.allocated)
                {
                    std::cerr << "*** " << CallSign << "[" << std::setw(6) << slot.bytes << "] missing #" << slot.allocated << std::endl;
                }
                while(slot.size>0)
                    quanta.releaseDyadic(i,slot.query());
                Memory::Stealth::DestructedAndZeroed(&slot);
            }
        }
    }

}
