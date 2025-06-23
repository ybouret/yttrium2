

//! \file

#ifndef Y_Sorting_AreDifferent_Included
#define Y_Sorting_AreDifferent_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    namespace Sorting
    {

        template <typename LHS_ITER, typename RHS_ITER>
        inline bool AreDifferent(LHS_ITER lhs, const size_t lhsCount,
                                 RHS_ITER rhs, const size_t rhsCount)
        {
            if(lhsCount!=rhsCount) return true;
            for(size_t i=lhsCount;i>0;--i,++lhs,++rhs)
            {
                if(*lhs != *rhs) return true;
            }
            return false;
        }
    }

}

#endif

