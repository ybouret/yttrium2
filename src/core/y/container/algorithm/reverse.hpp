//! \file

#ifndef Y_Container_Algorithm_Reverse_Included
#define Y_Container_Algorithm_Reverse_Included 1

#include "y/memory/stealth.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Algorithm
    {

        //! Generic Reverse Algorithm
        /**
         \param curr     current iterator
         \param size     number of items to reverse
         \param exchange exchange protocol
         */
        template <typename ITERATOR, typename EXCHANGE>   inline
        void Reverse(ITERATOR curr, size_t size, EXCHANGE &exchange)
        {
            size_t   nswp = size>>1; if(nswp<=0) return;
            ITERATOR last = curr+(--size);
            while(nswp-- > 0 )
                exchange(*(curr++),*(last--));
        }

        //! Reverse a sequence
        /**
         \param seq      sequence with begin() and size
         \param exchange exchange protocol
         */
        template <typename SEQUENCE, typename EXCHANGE> inline
        void Reverse(SEQUENCE &seq, EXCHANGE &exchange)
        {
            Reverse(seq.begin(), seq.size(), exchange);
        }




    }
}

#endif

