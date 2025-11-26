


//! \file

#ifndef Y_Memory_Buffer_Out_Of_Included
#define Y_Memory_Buffer_Out_Of_Included 1

#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Buffer Out Of a memory allocator
        //
        //
        //______________________________________________________________________
        template <typename ALLOCATOR>
        class BufferOutOf : public ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! acquire memory \param minimalLength bytes to acquire
            inline explicit BufferOutOf(const size_t minimalLength) noexcept  :
            bytes(minimalLength),
            entry( ALLOCATOR::Instance().acquire( Coerce(bytes) ) )
            {
            }

            //! cleanup
            inline virtual ~BufferOutOf() noexcept
            {
                static ALLOCATOR &mgr = ALLOCATOR::Location();
                mgr.release(Coerce(entry),Coerce(bytes));
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual size_t       length() const noexcept { return bytes; } //!< \return internal bytes
            inline virtual const void * ro()     const noexcept { return entry; } //!< \return internal memory

        private:
            Y_Disable_Copy_And_Assign(BufferOutOf); //!< discarding
            const size_t bytes; //!< capacity
            void * const entry; //!< memory location
        };
    }

}

#endif // !Y_Memory_Buffer_Out_Of_Included
