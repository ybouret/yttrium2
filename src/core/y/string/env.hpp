//! \file

#ifndef Y_ENV_Included
#define Y_ENV_Included 1

#include "y/string.hpp"

namespace Yttrium
{
    //! getting Environment variables
    struct Environment
    {

        static bool Get(String &value, const String &     name); //!< \param value output value \param name env name \return true if name exists, set value
        static bool Get(String &value, const char * const name); //!< \param value output value \param name env name \return true if name exists, set value

        static bool Flag(const String &     name); //!< \param name boolean env name \return true if name exists and means true or false
        static bool Flag(const char * const);      //!< wrapper \return true if env exists and means true or false

    };
}

#endif
