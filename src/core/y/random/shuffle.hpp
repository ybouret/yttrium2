
//! \file

#ifndef Y_Random_Shuffle_Included
#define Y_Random_Shuffle_Included 1

#include "y/random/bits.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Random
    {

        //! shuffle data
        struct Shuffle
        {

            

            //! Knuth Shuffle for iterator
            /**
             \param ran Bits
             \param a   original iterator using a[0..n-1]
             \param n   number of iterators
             */
            template <typename ITERATOR> static inline
            void Range(Bits &ran, ITERATOR a, const size_t n)
            {
                if(n<=1) return;
                for(size_t i=n-1;i>0;--i)
                    Memory::Stealth::Swap(a[i],a[ran.leq(i)]);
            }

            //! Knuth Shuffle for sequence with begin()/size()
            /**
             \param ran Bits
             \param seq sequence with begin() and size() method
             */
            template <typename SEQUENCE> static inline
            void Cxx(Bits &ran, SEQUENCE & seq) noexcept
            {
                Range(ran, seq.begin(), seq.size() );
            }


        };

    }

}

#endif // !Y_Random_Shuffle_Included
