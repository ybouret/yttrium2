

#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Model * Natural:: Mul(const Natural &lhs, const Natural &rhs)
        {
            return Model::Mul(Ops,*lhs.code,*rhs.code);
        }

#if 0
        Model * Natural:: Mul(const Natural &lhs, const natural_t rhs)
        {
            return Model::Mul(Ops,*lhs.code,rhs);
        }

        Model * Natural:: Mul(const natural_t lhs, const Natural &rhs)
        {
            return Mul(rhs,lhs);
        }
#endif



    }

}
