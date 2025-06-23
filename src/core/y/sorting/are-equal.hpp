
//! \file

#ifndef Y_Sorting_AreEqual_Included
#define Y_Sorting_AreEqual_Included 1

#include "y/system/compiler.hpp"


namespace Yttrium
{

    namespace Sorting
    {

        //! testing equality
        /**
         \param lhs      first iterator
         \param lhsCount number of available first
         \param rhs      second iterator
         \param rhsCount number of available second
         \return true iff equal ranges
         */
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

