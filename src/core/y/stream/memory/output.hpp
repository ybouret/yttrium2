
//! \file

#ifndef Y_Memory_Output_Stream_Included
#define Y_Memory_Output_Stream_Included 1

#include "y/stream/output.hpp"
#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{


    //__________________________________________________________________________
    //
    //
    //
    //! Memory area as OutputStream
    //
    //
    //__________________________________________________________________________
    class MemoryOutput : public OutputStream, public Memory::ReadOnlyBuffer
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
        explicit MemoryOutput(void * const entry, const size_t count) noexcept;


        //! setup from PERSISTENT buffer
        explicit MemoryOutput(Memory::ReadWriteBuffer &) noexcept;


        //! cleanup
        virtual ~MemoryOutput() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void write(const char c);
        virtual void flush();
        virtual void frame(const void * const addr, const size_t size);
        void         reset() noexcept;

        virtual const void * ro()     const noexcept;
        virtual size_t       length() const noexcept;


    private:
        Y_Disable_Copy_And_Assign(MemoryOutput); //!< discarding
        char *       curr; //!< current address
        char * const addr; //!< first valid   address
        char * const last; //!< first invalid address
    };

}

#endif
