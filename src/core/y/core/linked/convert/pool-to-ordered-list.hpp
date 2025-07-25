
//! \file

#ifndef Y_Core_Linked_Convert_Pool_To_Ordered_List_Included
#define Y_Core_Linked_Convert_Pool_To_Ordered_List_Included 1

#include "y/core/linked/convert/pool-to-list.hpp"

namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! converting pool to list with ordered list
        //
        //
        //______________________________________________________________________
        struct PoolToOrderedList
        {
            //__________________________________________________________________
            //
            //
            //! one-pass pool to list then sortByIncreasingAddress
            /**
             \param list an empty Linked::LIST
             \param pool a Linked::POOL, 
             */
            //__________________________________________________________________
            template <typename LIST, typename POOL> static inline
            void Convert(LIST &list, POOL &pool) noexcept
            {
                PoolToList::Convert(list,pool);
                list.sortByIncreasingAddress();
            }
        };

    }

}

#endif

