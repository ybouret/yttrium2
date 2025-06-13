//! \file

#ifndef Y_Heap_Sort_H_Included
#define Y_Heap_Sort_H_Included 1

#include "y/sorting/types.h"
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif


    void   Y_HeapSort(void * const  arr,
                      const size_t  num,
                      const size_t  alen,
                      void * const  rra,
                      Y_CompareProc const proc,
                      void * const  args
                      );


#if defined(__cplusplus)
}
#endif

#endif

