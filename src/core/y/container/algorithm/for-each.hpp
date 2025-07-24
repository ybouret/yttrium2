

//! \file

#ifndef Y_Container_Algo_ForEach_Included
#define Y_Container_Algo_ForEach_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Algo
    {

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

