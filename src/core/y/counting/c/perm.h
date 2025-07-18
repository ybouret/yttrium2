
//! \file

#ifndef Y_Counting_Perm_Include
#define Y_Counting_Perm_Include 1

#include "y/system/compiler.hpp"

#if defined(__cplusplus)
extern "C" {
#endif

    /**! context for permutatons */
    struct Y_Perm
    {
        size_t   n; //!< among n, count will be n!
    };

    /**! set n
     \param param data
     \param n     number of objects
     */
    void    Y_Perm_Init(struct Y_Perm *          param, size_t n);
    
    /**! perm[1..n] = [1..n]
     \param param data
     \param perm  boot indices
     */
    void    Y_Perm_Boot(const struct Y_Perm * param, size_t *perm);

    /**! next permutation
     \param param data
     \param perm  next indices
     \return 0 when done
     */
    int     Y_Perm_Next(const struct Y_Perm * param, size_t *perm);

#if defined(__cplusplus)
}
#endif


#endif
