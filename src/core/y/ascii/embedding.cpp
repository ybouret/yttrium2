
#include "y/ascii/embedding.hpp"


namespace Yttrium
{
    namespace ASCII
    {
        const char * const Embedding:: Char[256] =
        {
#include "embedding.hxx"
        };

        const char * Embedding:: Text(const char c) noexcept
        {
            return Char[ static_cast<uint8_t>(c) ];
        }
    }

}

