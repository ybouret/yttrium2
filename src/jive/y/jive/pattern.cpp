
#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Pattern:: Pattern(const uint32_t t) noexcept :
        uuid(t),
        next(0),
        prev(0),
        self(0)
        {
        }

        Pattern:: ~Pattern() noexcept
        {
        }

        Pattern:: Pattern(const Pattern &p) noexcept :
        CountedObject(),
        Vizible(),
        Serializable(),
        uuid(p.uuid),
        next(0),
        prev(0),
        self(0)
        {

        }

        bool Pattern:: feeble() const { return !strong(); }
    }

}
