//! \file


#ifndef Y_Core_Variadic_Included
#define Y_Core_Variadic_Included 1

#include "y/check/printf.hpp"
#include "y/system/types.hpp"


namespace Yttrium
{
    namespace Core
    {
        //______________________________________________________________________
        //
        //
        //
        //! Helper witht variadic formatting
        //
        //
        //______________________________________________________________________
        struct Variadic
        {
            //__________________________________________________________________
            //
            //
            //! format a buffer with address of a prepared va_list
            /**
             \param outputBuffer valid memory buffer
             \param outputLength valid buffer length
             \param formatString C-style format string
             \param vaListAddress address of a prepared vaList
             \return value of vsnprintf
             */
            //
            //__________________________________________________________________
            static int Format(char * const       outputBuffer,
                              const size_t       outputLength,
                              const char * const formatString,
                              void * const       vaListAddress) noexcept;

            //__________________________________________________________________
            //
            //
            //! example of Format() usage
            /**
             \param outputBuffer valid memory buffer
             \param outputLength valid buffer length
             \param formatString C-style format string
             \return value of vsnprintf
             **/
            //__________________________________________________________________
            static int Sprintf(char * const       outputBuffer,
                               const size_t       outputLength,
                               const char * const formatString,
                              ...) noexcept Y_Printf_Check(3,4);
         };
    }
}

#endif

