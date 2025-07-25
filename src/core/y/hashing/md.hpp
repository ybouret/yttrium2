
//! \file
#ifndef Y_HASHING_MD_INCLUDED
#define Y_HASHING_MD_INCLUDED 1


#include "y/hashing/digest.hpp"

namespace Yttrium
{



    namespace Hashing
    {
        class Function;

        //______________________________________________________________________
        //
        //
        //! message digests
        //
        //______________________________________________________________________
        struct MD
        {
            static Digest Of(Function &);                                   //!< \return content to digest
            static Digest Of(Function &, const void * const ,const size_t); //!< \return block to digest
            static Digest Of(Function &, const char * const);               //!< \return text to digest
            static Digest Of(Function &, const Memory::ReadOnlyBuffer &);   //!< \return buffer to digest
        };


    }

}


#endif
