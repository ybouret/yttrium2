
#include "y/ink/image/codec.hpp"


namespace Yttrium
{
    namespace Ink
    {

        Codec:: ~Codec() noexcept
        {
        }

        const String & Codec:: key() const noexcept { return name; }

    }

}
