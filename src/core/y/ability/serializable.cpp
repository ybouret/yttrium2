
#include "y/ability/serializable.hpp"


namespace Yttrium
{
    Serializable:: ~Serializable() noexcept
    {

    }

    Serializable:: Serializable() noexcept
    {
        
    }
}

#include "y/stream/misc/sequence.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    Core::String<char> Serializable:: toBinary() const
    {
        String str;
        SerializeTo(str,*this);
        return str;
    }
}


