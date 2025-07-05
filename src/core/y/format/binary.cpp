
#include "y/format/binary.hpp"
#include <cstring>

namespace Yttrium {

    void Binary:: ldz() noexcept
    {
        memset(array,0,sizeof(array));
    }
    
    Binary:: ~Binary() noexcept
    {
        Coerce(count) = 0;
        ldz();
    }

    Binary:: Binary(const Binary &other) noexcept :
    LegacyString(),
    count(other.count),
    array()
    {
        memcpy(array,other.array,sizeof(array));
    }

    const char * Binary:: c_str() const noexcept
    {
        return array;
    }


}
