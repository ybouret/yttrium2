
#include "y/stream/memory/input.hpp"
#include "y/memory/buffer/ro.hpp"
#include "y/check/usual.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    MemoryInput :: MemoryInput(const void * const entry, const size_t count) noexcept :
    curr( (const char *)entry ),
    addr( curr ),
    last( curr+count )
    {
        assert( Good(entry,count) );
    }

    MemoryInput :: MemoryInput(const Memory::ReadOnlyBuffer &buffer) noexcept :
    curr( (const char *)buffer.ro() ),
    addr( curr ),
    last( curr+buffer.length() )
    {
    }



    MemoryInput :: ~MemoryInput() noexcept
    {
        Coerce(curr) = 0;
        Coerce(addr) = 0;
        Coerce(last) = 0;
    }


    bool MemoryInput:: query(char &C)
    {
        if(curr<last) {
            C = *(curr++);
            return true;
        }
        return false;
    }

    void MemoryInput:: store(const char C)
    {
        static const char fn[] = "MemoryInput::store";
        if(curr<=addr) throw Specific::Exception(fn,"no prior query");
        const char target = curr[-1];
        if(C!=target)  throw Specific::Exception(fn,"mismatch characters");
        --curr;
    }

}
