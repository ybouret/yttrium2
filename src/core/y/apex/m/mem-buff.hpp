
//! \file

#ifndef Y_Apex_MemBuff_Included
#define Y_Apex_MemBuff_Included 1

#include "y/memory/buffer/rw.hpp"


namespace Yttrium
{

    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //
        //! Memory Buffer for local operations
        //
        //
        //______________________________________________________________________
        class MemBuff : public Memory::ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit MemBuff(const size_t minimalSize); //!< \param minimalSize minimal buffer size
            virtual ~MemBuff() noexcept;                //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t       length() const noexcept;
            virtual const void * ro()     const noexcept;

        private:
            Y_Disable_Copy_And_Assign(MemBuff); //!< discarding

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t   bytes; //!< allocated bytes
            const unsigned shift; //!< bytes = 2^shift
            void * const   entry; //!< memory entry
        };
    }

}

#endif // !Y_Apex_MemBuff_Included

