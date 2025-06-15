
//! \file

#ifndef Y_Memory_Input_Stream_Included
#define Y_Memory_Input_Stream_Included 1

#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace Memory { class ReadOnlyBuffer; }

    //__________________________________________________________________________
    //
    //
    //
    //! Memory area as InputStream
    //
    //
    //__________________________________________________________________________
    class MemoryInput : public InputStream
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup from PERSISTENT data
        /**
         \param entry memory address
         \param count memory bytes
         */
        explicit MemoryInput(const void * const entry, const size_t count) noexcept;

        //! setup from PERSISTENT buffer
        explicit MemoryInput(const Memory::ReadOnlyBuffer &) noexcept;

        //! cleanup
        virtual ~MemoryInput() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual bool query(char &);      //!< \return true iff read char
        virtual void store(const char);  //!< unread last read char

    private:
        Y_Disable_Copy_And_Assign(MemoryInput); //!< discarding
        const char *       curr; //!< current address
        const char * const addr; //!< first valid   address
        const char * const last; //!< first invalid address
    };

}

#endif

