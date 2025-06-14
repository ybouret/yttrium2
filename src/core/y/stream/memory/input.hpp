
//! \file

#ifndef Y_Memory_Input_Stream_Included
#define Y_Memory_Input_Stream_Included 1

#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace Memory { class ReadOnlyBuffer; }
    
    class MemoryInput : public InputStream
    {
    public:
        
        explicit MemoryInput(const void * const entry, const size_t count) noexcept;
        explicit MemoryInput(const Memory::ReadOnlyBuffer &) noexcept;
        virtual ~MemoryInput() noexcept;


        virtual bool query(char &C);
        virtual void store(const char C);
        
    private:
        Y_Disable_Copy_And_Assign(MemoryInput);
        const char *       curr;
        const char * const addr;
        const char * const last;
    };

}

#endif

