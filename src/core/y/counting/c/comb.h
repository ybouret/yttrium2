//! \file

#ifndef YACK_COUNTING_COMB_INCLUDED
#define YACK_COUNTING_COMB_INCLUDED 1

#include "y/system/compiler.hpp"

#if defined(__cplusplus)
extern "C" {
#endif

    /**! context for combinations */
    struct Y_Comb
    {
        size_t n;        //!< width
        size_t k;        //!< space
        size_t nmk;      //!< n-k
    };

    /**! setup
     \param param data
     \param n     n>0
     \param k     1<=k<=n
     */
    void Y_Comb_Init(struct Y_Comb *       param, const size_t n, const size_t k);

    /**! comb[1..k]=[1..k]
     \param param data
     \param comb  boot indices
     */
    void Y_Comb_Boot(const struct Y_Comb * param, size_t *comb);

    /**! next combination
     \param param data
     \param comb  next indices
     \return 0 when done
     */
    int  Y_Comb_Next(const struct Y_Comb * param, size_t *comb);

#if defined(__cplusplus)
}
#endif


#endif
