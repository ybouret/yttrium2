//! \file

#ifndef Y_Core_Text_Included
#define Y_Core_Text_Included 1

#include "y/system/compiler.hpp"
#include "y/system/types.hpp"


namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! basis operations on legacy C-style strings
        //
        //
        //______________________________________________________________________
        struct Text
        {
            //! better strlen
            /**
             \param text a C-style string
             \return 0 == text ? 0 : strlen(text)
             */
            static size_t  Length(const char * const text) noexcept;

            //! better strcpy
            /**
             \param outputBuffer output buffer
             \param outputLength output length
             \param text         a C-style string
             \return copied outputBuffer, padded with zeros
             */
            static char *  Copy(char * const       outputBuffer,
                                const size_t       outputLength,
                                const char * const text) noexcept;
        };
    }

}

#endif

