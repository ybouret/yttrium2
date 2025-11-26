//! \file

#ifndef Y_Apex_Natural_LROMB_Included
#define Y_Apex_Natural_LROMB_Included 1

#include "y/apex/natural.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class LockedReadOnlyMemoryBuffer : public Memory::ReadOnlyBuffer
        {
        public:
            explicit LockedReadOnlyMemoryBuffer(const Natural &) noexcept;
            virtual ~LockedReadOnlyMemoryBuffer() noexcept;

            virtual const void * ro()      const noexcept;
            virtual size_t       length()  const noexcept;
            
        private:
            Y_Disable_Copy_And_Assign(LockedReadOnlyMemoryBuffer);
            const Natural    host;
            const ScopedLock keep;
        };
    }
}

#endif // !Y_Apex_Natural_LROMB_Included

