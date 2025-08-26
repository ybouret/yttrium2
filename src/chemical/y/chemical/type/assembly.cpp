#include "y/chemical/type/assembly.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Assembly:: ~Assembly() noexcept
        {
        }

        Assembly:: Assembly() noexcept : width(0)
        {
        }

        
        void Assembly:: enroll(const Entity &en) noexcept
        {
            InSituMax(Coerce(width),en.name.size());
        }

        std::ostream & Assembly:: display(std::ostream &os, const String &s, const Justify::Type j) const
        {
            return os << Justify(s,width,j);
        }
    }

}
