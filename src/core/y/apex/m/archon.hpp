
//! \file

#ifndef Y_Apex_Archon_Included
#define Y_Apex_Archon_Included 1

#include "y/apex/metrics.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory { class Quanta; }

    namespace Apex
    {
        class Archon : public Singleton<Archon, ClassLockPolicy>
        {
        public:
            static const char * const          CallSign;
            static const Longevity             LifeTime  = LifeTimeOf::ApexMemory;
            static const unsigned              MinShift  = Metrics::MinShift;
            static const unsigned              MaxShift  = Metrics::MaxShift;
            static const unsigned              NumShifts = Metrics::MaxShift - Metrics::MinShift + 1;
            class Slot;

            virtual void display(std::ostream &,size_t) const;
            void *       query(const unsigned shift);
            void         store(const unsigned shift, void * const block) noexcept;

        private:
            friend class Singleton<Archon, ClassLockPolicy>;
            Y_Disable_Copy_And_Assign(Archon);

            explicit Archon();
            virtual ~Archon() noexcept;

            Slot * const     slots;
            Memory::Quanta  &quanta;

        };

       
    }

}

#endif

