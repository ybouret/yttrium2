//! \file

#ifndef Y_Core_Text_Included
#define Y_Core_Text_Included 1

#include "y/system/compiler.hpp"
#include "y/system/compiler.hpp"


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

            //! better strncpy
            /**
             \param outputBuffer output buffer
             \param outputLength output length
             \param text         a C-style string
             \return copied outputBuffer, padded with zeros
             */
            static char *  Copy(char * const       outputBuffer,
                                const size_t       outputLength,
                                const char * const text) noexcept;

            //! remove spaces from end of text
            /**
             \param  text trimmed
             \return text
             */
			static char * Trim(char * const text) noexcept;

            //! better strncat
            /**
             \param outputBuffer output buffer
             \param outputLength output length
             \param text         a C-style string
             \return outputBuffer+text
            **/
            static char * Add(char * const       outputBuffer,
                              const size_t       outputLength,
                              const char * const text) noexcept;

            //! in place to lowercase conversion
            /**
             \param buffer buffer to convert
             \param buflen length to convert
             */
            static void ToLower(char * const buffer,
                                const size_t buflen) noexcept;
        };
    }

}

#endif

