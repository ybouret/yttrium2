

#include "y/stream/memory/output.hpp"
#include "y/check/usual.hpp"
#include "y/exception.hpp"
#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{
    static const char * const CallSign = "MemoryOutput";

    MemoryOutput :: MemoryOutput(void * const entry, const size_t count) noexcept :
    curr( (char *)entry ),
    addr( curr ),
    last( curr+count )
    {
        assert( Good(entry,count) );
    }

    MemoryOutput:: MemoryOutput(Memory::ReadWriteBuffer &buffer) noexcept :
    curr( (char *) buffer.rw() ),
    addr( curr ),
    last( curr + buffer.length() )
    {
    }



    MemoryOutput :: ~MemoryOutput() noexcept
    {
    }

    void MemoryOutput:: write(const char c)
    {
        if(curr>=last) throw Specific::Exception(CallSign,"write excess");
        *(curr)++ = c;
    }

    void MemoryOutput:: flush()
    {

    }

    
    void MemoryOutput:: reset() noexcept
    {
        curr = addr;
    }

    const void * MemoryOutput:: ro() const noexcept { return addr; }

    size_t MemoryOutput:: length() const noexcept { return size_t(curr-addr); }


}


