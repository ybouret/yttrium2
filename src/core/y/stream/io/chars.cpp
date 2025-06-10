
#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    namespace IO
    {
        Chars:: ~Chars() noexcept
        {
        }

        Chars:: Chars() noexcept : Concurrent::LiveList<Char>()
        {
        }

        
    }
}
