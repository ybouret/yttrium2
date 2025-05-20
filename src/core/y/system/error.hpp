
//! \file

#ifndef Y_System_Error_Included
#define Y_System_Error_Included 1


#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/system/types.hpp"

namespace Yttrium
{
    namespace Libc
    {
        //______________________________________________________________________
        //
        //
        //
        //! using errno/strerror API
        //
        //
        //______________________________________________________________________
        struct Error
        {
            typedef int Type; //!< alias

            //! format with strerror
            /**
             \param errorBuffer output buffer
             \param errorLength output buffer length
             \param errorCode   from errno
             \return formatted errorBuffer
             */
            static char * Format(char * const errorBuffer,
                                 const size_t errorLength,
                                 const Type   errorCode) noexcept;

            //! stop on critical error
            /**
             \param errorCode from errno
             \param title context of the error
             */
            static void Critical(const Type errorCode, const char * const title);
        };

    }

    namespace Windows
    {
        //______________________________________________________________________
        //
        //
        //
        //! using GetLastError()/FormatMessage API
        //
        //
        //______________________________________________________________________
        struct Error
        {
            typedef uint32_t Type; //!< alias

            //! format with strerror
            /**
             \param errorBuffer output buffer
             \param errorLength output buffer length
             \param errorCode   from GetLastError()
             \return formatted errorBuffer
             */
            static char * Format(char * const errorBuffer,
                                 const size_t errorLength,
                                 const Type   errorCode) noexcept;

            //! stop on critical error
            /**
             \param errorCode   from GetLastError()
             \param title       context title
             */
            static void Critical(const Type errorCode, const char * const title);

        };
    }

    namespace System
    {
#if defined(Y_BSD)
        typedef Libc::Error Error;
#endif

#if defined(Y_WIN)
        typedef Windows::Error Error;
#endif
    }




}

#endif

