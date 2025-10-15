
//! \file

#ifndef Y_String_Boolean_Included
#define Y_String_Boolean_Included 1

#include "y/system/compiler.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{

    //! converting string to boolean
    struct StringToBoolean
    {
        static bool MeansTrue(const char  * const lower) noexcept;                          //!< \param lower lowercase string \return true iff "1" or "on" of "true"
        static bool MeansFalse(const char * const lower) noexcept;                          //!< \param lower lowercase string \return true iff "0" or "off" or "false"

        //! check that buffer[buflen] is a boolean named field
        /**
         \param buffer input buffer
         \param buflen input length
         \param field  field name
         \return true if buffer[buflen] means true or false
         */
        static bool Get(const char *buffer, const size_t buflen, const char * const field);

        //! check that name if a boolean named field
        /**
         \param name string to test
         \param field field name
         \return true if name means true or false
         */
        static bool Get(const Core::String<char> &name, const char * const field);
    };

}

#endif // !Y_String_Boolean_Included
