
//! \file

#ifndef Y_Color_Print_Included
#define Y_Color_Print_Included

#include "y/type/traits.hpp"
#include "y/type/pick.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Color
    {
        namespace Privy
        {
            template <typename T, const bool OneByte> struct Print;

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename T> struct Print<T,false>
            {
                static inline std::ostream & To( std::ostream &os, const T value)
                {
                    return os << value;
                }
            };

            template <typename T> struct Print<T,true>
            {
                static inline std::ostream & To( std::ostream &os, const T value)
                {
                    return os << (int)value;
                }
            };
#endif  

        }

        template <typename T> static inline
        std::ostream & Print(std::ostream &os, const T value)
        {
            return Privy::Print<T,1==sizeof(T)>::To(os,value);
        }



    }

}

#endif // !Y_Color_Print_Included

