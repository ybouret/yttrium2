#include "y/apex/metrics.hpp"
#include "y/memory/allocator/quanta.hpp"
#include "y/core/linked/pool.hpp"
#include <iomanip>
#include "y/xml/attribute.hpp"
#include "y/system/exception.hpp"
#include "y/decimal.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Apex
    {

        class Archon : public Singleton<Archon, ClassLockPolicy>
        {
        public:
            static const char * const          CallSign;
            static const Longevity             LifeTime  = 1010;
            static const unsigned              MinShift  = Metrics::MinShift;
            static const unsigned              MaxShift  = Metrics::MaxShift;
            static const unsigned              NumShifts = Metrics::MaxShift - Metrics::MinShift + 1;
            typedef Core::PoolOf<Memory::Page> SlotType;

            class Slot : public SlotType
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


            virtual void display(std::ostream &os,size_t indent) const
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

            void * query(const unsigned shift)
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

            void store(const unsigned shift, void * const block) noexcept
            {
                Y_Lock(access);
                assert(shift>=MinShift);
                assert(shift<=MaxShift);
                Slot &slot = slots[shift];
                assert(slot.allocated>0);
                slot.store( Memory::Page::Cast(block) );
                --slot.allocated;
            }


        private:
            friend class Singleton<Archon, ClassLockPolicy>;
            Y_Disable_Copy_And_Assign(Archon);

            explicit Archon();
            virtual ~Archon() noexcept;

            Slot * const     slots;
            Memory::Quanta  &quanta;

        };

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
                    std::cerr << "*** Archon[" << std::setw(6) << slot.bytes << "] missing #" << slot.allocated << std::endl;
                }
                while(slot.size>0)
                    quanta.releaseDyadic(i,slot.query());
                Memory::Stealth::DestructedAndZeroed(&slot);
            }
        }

        class BlockAPI
        {
        public:
            explicit BlockAPI(const size_t n) noexcept : size(0), capacity(n)
            {
            }

            virtual ~BlockAPI() noexcept
            {
            }

            const size_t   size;       //!< most significant word
            const size_t   capacity;   //!< maximum size

        protected:
            void release(const unsigned shift,
                         void * const   entry) noexcept
            {
                static Archon &archon = Archon::Location();
                archon.store(shift,entry);
            }

        private:
            Y_Disable_Copy_And_Assign(BlockAPI);
        };

        template <typename T>
        class Block : public BlockAPI
        {
        public:

            explicit Block(void * const   entry,
                           const size_t   count,
                           const unsigned shift) noexcept :
            BlockAPI(count),
            data( static_cast<T *>(entry) ),
            shft(shift)
            {
            }

            virtual ~Block() noexcept
            {
                release(shft,data);
            }

            T * const      data; //!< workspace
            const unsigned shft; //!< workspace size = 2^shift

        private:
            Y_Disable_Copy_And_Assign(Block);
        };



    }
}

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    struct Blk
    {
        unsigned shift;
        void *   entry;
    };

    static const size_t MaxBlk = 30;
    static Blk          Blks[MaxBlk];
}

Y_UTEST(apex_block)
{
    System::Rand ran;

    Y_PRINTV(Apex::Archon::NumShifts);
    Y_SIZEOF(Apex::ArchonSlots_);

    Apex::Archon & mgr = Apex::Archon::Instance();

    if(true)
    {
        mgr.display(std::cerr,0);
        Y_Memory_BZero(Blks);
        for(size_t i=0;i<MaxBlk;++i)
        {
            Blk &b  = Blks[i];
            while( (b.shift = unsigned(ran.in(20)) ) < Apex::Archon::MinShift )
                ;
            b.entry = mgr.query(b.shift);
        }
        ran.shuffle(Blks,MaxBlk);

        mgr.display(std::cerr,0);

        for(size_t i=0;i<MaxBlk;++i)
        {
            Blk &b  = Blks[i];
            mgr.store(b.shift,b.entry);
        }
        mgr.display(std::cerr,0);
    }


}
Y_UDONE()

