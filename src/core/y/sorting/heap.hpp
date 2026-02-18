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
        //______________________________________________________________________
        //
        //
        //
        //! Heap sort implementation and interfaces
        //
        //
        //______________________________________________________________________
        struct Heap
        {
            //__________________________________________________________________
            //
            //
            //! heapsort, C-style
            /**
             \param arr objects[alen*(0..num-1)]
             \param num count of objects
             \param alen bytes per object
             \param rra  auxiliary space [alen]
             \param proc legacy comparison
             \param args legacy arguments
             */
            //__________________________________________________________________
            static void   Sort(void * const  arr,
                               const size_t  num,
                               const size_t  alen,
                               void * const  rra,
                               Compare const proc,
                               void * const  args
                               );


            //__________________________________________________________________
            //
            //
            //
            //! Tableau sorting
            /**
             \param arr T[0..num-1]
             \param num number of objects
             \param cmp object-wise comparator
             */
            //
            //__________________________________________________________________
            template <typename T, typename COMPARE> static inline
            void  Sort(T * const    arr,
                       const size_t num,
                       COMPARE     &cmp)
            {
                assert(Good(arr,num));
                void * rra[ Alignment::WordsFor<T>::Count ];
                Sort(arr, num, sizeof(T), rra, CompareWrapper<T,COMPARE>::Call, (void*)&cmp);
            }

            template <typename CONTIGUOUS, typename COMPARE> static inline
            void Sort(CONTIGUOUS &arr, COMPARE &cmp)
            {
                Sort(arr(),arr.size(),cmp);
            }

            //__________________________________________________________________
            //
            //
            //! co-heapsort, C-style
            /**
             \param arr primary[alen*(0..num-1)]
             \param brr replica[blen*(0..num-1)]
             \param num count of objects
             \param alen bytes per primary
             \param rra  auxiliary space [alen]
             \param blen bytes per replica
             \param rrb  auxiliary space [blen]
             \param proc legacy comparison
             \param args legacy arguments
             */
            //__________________________________________________________________
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

            //__________________________________________________________________
            //
            //
            //
            //! Tableaux co-sorting
            /**
             \param arr T[0..num-1]
             \param brr U[0..num-1]
             \param num number of objects
             \param cmp object-wise comparator
             */
            //
            //__________________________________________________________________
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

#endif // !Y_Sorting_Heap_Included

