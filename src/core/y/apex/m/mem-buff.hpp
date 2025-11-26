
//! \file

#ifndef Y_Apex_MemBuff_Included
#define Y_Apex_MemBuff_Included 1

#include "y/memory/buffer/rw.hpp"


namespace Yttrium
{

    namespace Apex
    {
        class MemBuff : public Memory::ReadWriteBuffer
        {
        public:
            explicit MemBuff(const size_t minimalSize);
            virtual ~MemBuff() noexcept;


        private:
            Y_Disable_Copy_And_Assign(MemBuff);
            const size_t   bytes;
            const unsigned shift;
            void * const   entry;
        };
    }

}

#endif // !Y_Apex_MemBuff_Included

