//! \file

#ifndef Y_Sorting_Heap_Included
#define Y_Sorting_Heap_Included 1

#include "y/type/sign.hpp"
#include "y/check/usual.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium{

    namespace Sorting
    {
        struct Heap
        {
            //! arr[width*(0..num-1)]
            static void   Sort(void * const arr,
                               const size_t num,
                               const size_t alen,
                               void * const rra,
                               int        (*proc)(const void * const, const void * const, void * const),
                               void * const args
                               );


            //! sorting [0..num-1]
            template <typename T, typename COMPARE> static inline
            void  Sort(T * const    arr,
                       const size_t num,
                       COMPARE     &cmp)
            {
                assert(Good(arr,num));
                struct Proc {
                    static inline int Call(const void * const lhs, const void * const rhs, void * const args)
                    {
                        assert(0!=lhs); assert(0!=rhs); assert(0!=args);
                        COMPARE &cmp = *(COMPARE *)args;
                        return int( cmp( *(const T*)lhs, *(const T*)rhs));
                    }
                };
                void * rra[ Alignment::WordsFor<T>::Count ];
                Sort(arr, num, sizeof(T), rra, Proc::Call, (void*)&cmp);
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

        };
    }

}

#endif

