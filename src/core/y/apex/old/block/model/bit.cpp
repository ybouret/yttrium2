
#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {

        void Model:: shr() noexcept
        {
            switch(view)
            {
                case View8:  Coerce(bits) = block<uint8_t>() .shr(sync[0]); break;
                case View16: Coerce(bits) = block<uint16_t>().shr(sync[1]); break;
                case View32: Coerce(bits) = block<uint32_t>().shr(sync[2]); break;
                case View64: Coerce(bits) = block<uint64_t>().shr(sync[3]); break;
            }
        }


    }

}
