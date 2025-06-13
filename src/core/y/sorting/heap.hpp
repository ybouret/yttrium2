//! \file

#ifndef Y_Sorting_Heap_Included
#define Y_Sorting_Heap_Included 1

#include "y/sorting/types.hpp"
#include "y/type/sign.hpp"
#include "y/check/usual.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium{

    namespace Sorting
    {
        struct Heap
        {
            //! arr[width*(0..num-1)]
            static void   Sort(void * const  arr,
                               const size_t  num,
                               const size_t  alen,
                               void * const  rra,
                               Compare const proc,
                               void * const  args
                               );


            //! sorting [0..num-1]
            template <typename T, typename COMPARE> static inline
            void  Sort(T * const    arr,
                       const size_t num,
                       COMPARE     &cmp)
            {
                assert(Good(arr,num));
                void * rra[ Alignment::WordsFor<T>::Count ];
                Sort(arr, num, sizeof(T), rra, CompareWrapper<T,COMPARE>::Call, (void*)&cmp);
            }

            static void   Sort(void * const arr,
                               void * const brr,
                               const size_t num,
                               const size_t alen,
                               void * const rra,
                               const size_t blen,
                               void * const rrb,
                               int        (*proc)(const void * const, const void * const, void * const),
                               void * const args
                               );

            //! sorting [0..num-1]
            template <typename T, typename U, typename COMPARE> static inline
            void  Sort(T * const    arr,
                       U * const    brr,
                       const size_t num,
                       COMPARE     &cmp)
            {
                assert(Good(arr,num));
                assert(Good(brr,num));
                void * rra[ Alignment::WordsFor<T>::Count ];
                void * rrb[ Alignment::WordsFor<U>::Count ];
                Sort(arr, brr, num, sizeof(T), rra, sizeof(U), rrb, CompareWrapper<T,COMPARE>::Call, (void*)&cmp);
            }
        };
    }

}

#endif

