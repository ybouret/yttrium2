#include "y/stream/io/char.hpp"

namespace Yttrium
{
    namespace IO
    {
        Char:: Char(const uint8_t a) noexcept :
        next(0),
        prev(0),
        code(a)
        {
        }

        Char:: ~Char() noexcept
        {
            
        }

        Char:: Char(const Char &ch) noexcept :
        next(0),
        prev(0),
        code(ch.code)
        {}

    }
}

