//! \file

#ifndef YACK_COUNTING_INTS_INCLUDED
#define YACK_COUNTING_INTS_INCLUDED 1

#include "y/system/compiler.hpp"

#if defined(__cplusplus)
extern "C" {
#endif
    
    /**! context for integer partitions */
    struct Y_Part
    {
        size_t   n; //!< the positive integer
        size_t   k; //!< current number of  parts
    };

    /**! intialize
     \param param data
     \param n     positive integer to part
     */
    void    Y_Part_Init(struct Y_Part *param, size_t n);
   
    /**! ints[1] = [n], k=1
     \param param data
     \param ints  boot indices
     */
    void    Y_Part_Boot(struct Y_Part *param, size_t *ints);
    
    /**! next partition
     \param param data
     \param ints  next indices
     \return 0 when done
     */
    int     Y_Part_Next(struct Y_Part *param, size_t *ints);
    

#if defined(__cplusplus)
}
#endif


#endif
