
#include "y/apex/block/api.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Apex
    {
        BlockAPI:: BlockAPI(const size_t   n,
                           const ViewType v) :
        size(0),
        maxi(n),
        view(v)
        {
        }

        BlockAPI:: ~BlockAPI() noexcept
        {

        }

        bool BlockAPI:: isValid() const noexcept
        {
            Y_Block_Check(size<=maxi);
            return doCheck();
        }

        std::ostream & operator<<(std::ostream &os, const BlockAPI &self)
        {
            return self.print(os);
        }

        const ViewType BlockAPI::VTable[] =
        {
            View8, View16, View32, View64
        };

        
    }

}


