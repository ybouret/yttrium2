
//! \file

#ifndef Y_Random_Shufflel_Included
#define Y_Random_Shufflel_Included 1

#include "y/random/bits.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Random
    {

        //! shuffle data
        struct Shuffle
        {

            //! Knuth Shuffle
            /**
             \param ran Bits
             \param a   original iterator
             \param n   number of iterators
             */
            template <typename ITER> static inline
            void Range(Bits &ran, ITER a, const size_t n)
            {
                if(n<=1) return;
                for(size_t i=n-1;i>0;--i)
                    Memory::Stealth::Swap(a[i],a[ran.leq(i)]);
            }

        };

    }

}

#endif
