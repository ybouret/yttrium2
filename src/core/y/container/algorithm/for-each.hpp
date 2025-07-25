

//! \file

#ifndef Y_Container_Algo_ForEach_Included
#define Y_Container_Algo_ForEach_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Algo
    {

        //! apply method for each object in range
        /**
         \param iter current iterator
         \param size number of items
         \param meth method to call
         */
        template <
        typename ITER,
        typename METH> inline
        void ForEach(ITER iter, size_t size, METH meth)
        {
            while(size-- > 0)
            {
                ( (*iter++).*meth )();
            }
        }
    }

}
#endif

