//! \file

#ifndef Y_Information_BWT_Included
#define Y_Information_BWT_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Information
    {
        
        struct BWT
        {
            /**! forward Burrows Wheeler Transform, returns the primary index */
            static size_t  Encode(void        * const output,
                                  const void  * const input,
                                  const size_t        size,
                                  size_t      * const indices);
            
            
            
            
            
            /**! reverse Burrows Wheeler Transform  using the primary index */
            static void    Decode(void        * const output,
                                  const void  * const input,
                                  const size_t        size,
                                  size_t      * const indices,
                                  const size_t primary_index);
            
        };
        
    }
}


#endif
