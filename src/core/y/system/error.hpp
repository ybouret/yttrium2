
//! \file

#ifndef Y_System_Error_Included
#define Y_System_Error_Included 1


#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"
#include "y/check/printf.hpp"

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
             \param fmt       context of the error
             */
            static void Critical(const Type errorCode,
                                 const char * const fmt,
                                 ...) noexcept Y_Printf_Check(2,3);
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
             \param fmt         context of the error
             */
            static void Critical(const Type errorCode, const char * const fmt,...) noexcept;
        };
    }

#if defined(Y_Darwin)
    namespace Mach
    {

        struct Error
        {
            typedef int Type; //!< alias to mach_error_t

            //! format with mach_error_string
            /**
             \param errorBuffer output buffer
             \param errorLength output buffer length
             \param errorCode   a mach_error_t
             \return formatted errorBuffer
             */
            static char * Format(char * const errorBuffer,
                                 const size_t errorLength,
                                 const Type   errorCode) noexcept;

            static void Critical(const Type         errorCode,
                                 const char * const fmt,
                                 ...) noexcept Y_Printf_Check(2,3);

        };
    }
#endif

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

