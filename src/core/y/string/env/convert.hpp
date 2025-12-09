
//! \file

#ifndef Y_ENV_Convert_Included
#define Y_ENV_Convert_Included 1

#include "y/string/env.hpp"
#include "y/ascii/convert.hpp"

namespace Yttrium
{

    struct EnvironmentConvert
    {
        template <typename T> static inline
        T To(const String &name, typename TypeTraits<T>::ParamType defaultValue)
        {
            String value;
            if( Environment::Get(value,name) )
            {
                return ASCII::Convert::To<T>(value,name.c_str());
            }
            else
                return defaultValue;
        }

        template <typename T> static inline
        T To(const char * const name, typename TypeTraits<T>::ParamType defaultValue)
        {
            const String _(name); return To<T>(_,defaultValue);
        }
    };

}

#endif // !Y_ENV_Convert_Included
