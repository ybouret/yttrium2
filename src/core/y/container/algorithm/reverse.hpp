//! \file

#ifndef Y_Container_Algorithm_Reverse_Included
#define Y_Container_Algorithm_Reverse_Included 1

#include "y/memory/stealth.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Algorithm
    {


        template <typename ITERATOR, typename EXCHANGE>   inline
        void Reverse(ITERATOR curr, size_t size, EXCHANGE &exchange)
        {
            size_t   nswp = size>>1; if(nswp<=0) return;
            ITERATOR last = curr+(--size);
            while(nswp-- > 0 )
                exchange(*(curr++),*(last--));
        }
        




    }
}

#endif

