
//! \file

#ifndef Y_Sorting_AreEqual_Included
#define Y_Sorting_AreEqual_Included 1

#include "y/sorting/types.hpp"
#include "y/type/sign.hpp"

namespace Yttrium
{

    namespace Sorting
    {

        template <typename LHS_ITER, typename RHS_ITER>
        inline bool AreEqual(LHS_ITER lhs, const size_t lhsCount,
                             RHS_ITER rhs, const size_t rhsCount)
        {
            if(lhsCount!=rhsCount) return false;
            for(size_t i=lhsCount;i>0;--i,++lhs,++rhs)
            {
                if(*lhs != *rhs) return false;
            }
            return true;
        }
    }

}

#endif

