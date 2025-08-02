
#include "y/jive/tag.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Tag:: ~Tag() noexcept
        {
        }

        Tag:: Tag(const Tag &tag) noexcept : TagType(tag) {}

        Tag:: Tag(String * const p) noexcept : TagType(p) {}

    }

}

