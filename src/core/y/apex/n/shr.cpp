#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {

        void Natural:: shr() noexcept
        {
            assert(0!=code);
            code->shr();
        }
    }

}
