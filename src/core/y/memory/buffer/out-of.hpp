


//! \file

#ifndef Y_Memory_StaticBuffer_Included
#define Y_Memory_StaticBuffer_Included 1

#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename ALLOCATOR>
        class BufferOutOf : public ReadWriteBuffer
        {
        public:
            inline explicit BufferOutOf(const size_t minimalLength) noexcept  :
            bytes(minimalLength),
            entry( ALLOCATOR::Instance().acquire( Coerce(bytes) ) )
            {
            }

            inline virtual ~BufferOutOf() noexcept
            {
                static ALLOCATOR &mgr = ALLOCATOR::Location();
                mgr.release(Coerce(entry),Coerce(bytes));
            }

            inline virtual size_t       length() const noexcept { return bytes; }
            inline virtual const void * ro()     const noexcept { return entry; }

        private:
            Y_Disable_Copy_And_Assign(BufferOutOf);
            const size_t bytes;
            void * const entry;
        };
    }

}

#endif
