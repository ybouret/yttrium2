
//! \file

#ifndef Y_Sorting3_Included
#define Y_Sorting3_Included 1

#include "y/sorting/types.hpp"
#include "y/type/sign.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Sorting
    {
        //! sorting a triplet in ascending order \param arr arr[0..2]
        template <typename T> inline
        void Sort3(T arr[])
        {
            // insert arr[1]
            if (arr[1] < arr[0])
                Swap(arr[0], arr[1]);

            // insert arr[2]
            if (arr[2] < arr[1])
            {
                Swap(arr[1], arr[2]);
                if (arr[1] < arr[0])
                    Swap(arr[1], arr[0]);
            }
        }

        //! sorting a triplet according to comparator
        /**
         \param arr arr[0..2]
         \param cmp SignType cmp(lhs,rhs)
         */
        template <typename T, typename COMPARE>  inline
        void  Sort3(T * const    arr,
                    COMPARE     &cmp)
        {
            assert(0 != arr);
            
            // insert arr[1]
            if( cmp(arr[1], arr[0]) == Negative )
                Swap(arr[0], arr[1]);

            // insert arr[2]
            if( cmp(arr[2],arr[1]) == Negative )
            {
                Swap(arr[1], arr[2]);
                if ( cmp(arr[1],arr[0]) == Negative )
                    Swap(arr[1], arr[0]);
            }
        }
    }

}

#endif

