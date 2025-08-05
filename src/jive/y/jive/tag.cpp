
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


        Tag:: Tag(const String &s) : TagType( new String(s) ) {}

        Tag:: Tag(const char * const s) : TagType( new String(s) ) {}

        Tag:: Tag(const char c) : TagType( new String(c) ) {}
    }

}

