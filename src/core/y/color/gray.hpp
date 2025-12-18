
//! \file

#ifndef Y_Color_Gray_Included
#define Y_Color_Gray_Included

#include "y/type/list.hpp"
#include <cmath>

namespace Yttrium
{
    namespace Color
    {

        //______________________________________________________________________
        //
        //
        //
        //! color/gray operations
        //
        //
        //______________________________________________________________________
        struct Gray
        {
            //! table of unit floating points
            template <typename T>
            struct ByteTo {
                static const T Unit[256]; //!< precomputed unit floating points
            };

            static inline uint8_t UnitToByte(const float &x) noexcept
            {
                return (uint8_t) floorf(x*256.0f + 0.5f);;
            }

            static inline uint8_t UnitToByte(const double &x) noexcept
            {
                return (uint8_t) floor(x*256.0 + 0.5);
            }

            static inline uint8_t UnitToByte(const long double &x) noexcept
            {
                return (uint8_t) floorl(x*256.0L + 0.5L);
            }




            static const size_t  Count = 1 + 3*255; //!< r+g+b possilities
            static const uint8_t Table[Count];      //!< gray level from r+g+b

            static inline
            uint8_t ToByte(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return Table[ unsigned(r) + unsigned(g) + unsigned(b) ];
            }

            template <typename T> static inline
            T ToUnit(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return ByteTo<T>::Unit[ ToByte(r,g,b) ];
            }

            template <typename T> struct To
            {
                static inline T Get(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
                {
                    return ToUnit<T>(r,g,b);
                }
            };

        };

        template <> struct Gray::To<uint8_t>
        {
            static inline uint8_t Get(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return ToByte(r,g,b);
            }
        };
    }
}


#endif // !Y_Color_Gray_Included
