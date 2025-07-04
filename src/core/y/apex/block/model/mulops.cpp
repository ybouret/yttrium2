
#include "y/apex/block/model/mulops.hpp"

namespace Yttrium
{
    namespace Apex
    {
        MulOps::Case MulOps::Get(const size_t lhs, const size_t rhs) noexcept
        {

            switch(lhs)
            {
                case 0:
                    switch(rhs)
                    {
                        case 0:  break;
                        case 1:  return Case01;
                        default: return Case0N;
                    }
                    break;

                case 1:
                    switch(rhs)
                    {
                        case 0:  return Case10;
                        case 1:  return Case11;
                        default: return Case1N;
                    }
                    break;

                default:
                    switch(rhs)
                    {
                        case 0:  return CaseN0;
                        case 1:  return CaseN1;
                        default: return CaseNN;
                    }
                    break;
            }

            assert(0==lhs&&0==rhs);
            return Case00;
        }
    }

}

