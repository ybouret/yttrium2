//! \file

#ifndef Y_Information_BWT_Included
#define Y_Information_BWT_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Information
    {
        //! Burrows-Wheeler Transform
        struct BWT
        {
            //! forward Burrows Wheeler Transform
            /**
             \param output  output buffer
             \param input   input buffer
             \param size    input/output buffer size
             \param indices indices[size]
             \return the primary index
             */
            static size_t  Encode(void        * const output,
                                  const void  * const input,
                                  const size_t        size,
                                  size_t      * const indices);
            
            
            
            
            
            //! reverse Burrows Wheeler Transform
            /**
             \param output  output buffer
             \param input   input buffer
             \param size    input/output buffer size
             \param indices indices[size]
             \param primary_index from Encode()
             */
            static void    Decode(void        * const output,
                                  const void  * const input,
                                  const size_t        size,
                                  size_t      * const indices,
                                  const size_t primary_index);
            
        };
        
    }
}


#endif
