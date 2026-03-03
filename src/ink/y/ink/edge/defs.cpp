#include "y/ink/edge/defs.hpp"

namespace Yttrium
{
    namespace Ink
    {
        uint8_t EdgeIs:: NamedFrom(const uint8_t flag) noexcept
        {
            static const uint8_t Both = Strong | Feeble;

            switch(flag & Both )
            {
                case Both:
                case Strong : return Strong;
                case Feeble : return Feeble;
                default:
                    break;
            }
            return Absent;
        }

    }

}
