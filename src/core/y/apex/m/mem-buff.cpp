
#include "y/apex/m/mem-buff.hpp"
#include "y/apex/m/archon.hpp"
#include "y/exception.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{

    namespace Apex
    {

        static inline
        void * getBlock(size_t & bytes, unsigned &shift )
        {
            static const char  fn[]    = "Apex::MemBuff";
            static const size_t _1     = 1;
            static Archon &     archon = Archon:: Instance();

            if(bytes>Base2<size_t>::MaxBytes)
                throw Specific::Exception(fn,"bytes overflow");

            shift = CeilLog2(bytes);
            if(shift>Archon::MaxShift)
                throw Specific::Exception(fn,"shift overflow");

            shift = Max(shift,Archon::MinShift);
            bytes = _1 << shift;

            return archon.query(shift);
        }

        MemBuff:: MemBuff(const size_t minimalSize) :
        Memory::ReadWriteBuffer(),
        bytes(minimalSize),
        shift(0),
        entry( getBlock( Coerce(bytes), Coerce(shift)) )
        {
            
        }


        MemBuff:: ~MemBuff() noexcept
        {
            static Archon & archon = Archon:: Location();
            archon.store(shift,entry);
            Coerce(bytes) = 0;
            Coerce(shift) = 0;
            Coerce(entry) = 0;
        }
    }

}
