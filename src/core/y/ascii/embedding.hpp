
//! \file

#ifndef Y_Text_ASCII_Embedding_Included
#define Y_Text_ASCII_Embedding_Included 1

#include "y/system/compiler.hpp"


namespace Yttrium
{
    namespace ASCII
    {
        //______________________________________________________________________
        //
        //
        //
        //! escaped chars to write labels for Doxygen of C code
        //
        //
        //______________________________________________________________________
        struct Embedding
        {
            static const char * const Char[256]; //!< table of substitution
            static const char *       Text(const char) noexcept; //!< \return convert char to text
        };

    }
}

#endif

