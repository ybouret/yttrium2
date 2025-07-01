
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {
        SignType Natural:: Compare(const Natural &lhs, const natural_t rhs) noexcept
        {
            return Model::Compare(*lhs.code,rhs);
        }

        SignType Natural:: Compare(const natural_t lhs, const Natural &rhs) noexcept
        {
            return Sign::Opposite( Model::Compare(*rhs.code,lhs) );
        }
    }

}

