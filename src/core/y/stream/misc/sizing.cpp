
#include "y/stream/misc/sizing.hpp"

namespace Yttrium
{

    SizingOutput:: ~SizingOutput() noexcept
    {
    }

    SizingOutput:: SizingOutput() noexcept : OutputStream(), result(0)
    {
    }

    void SizingOutput:: write(const char)
    {
        ++Coerce(result);
    }

    void SizingOutput:: flush()
    {
        
    }

}

