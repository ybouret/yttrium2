
//! \file

#ifndef Y_Color_Gray_Included
#define Y_Color_Gray_Included

#include "y/type/list.hpp"
#include <cmath>

namespace Yttrium
{
    namespace Color
    {

        //! table of unit floating points
        template <typename T>
        struct ByteTo;


        //! table for float
        template <> struct ByteTo<float>
        { static const float       Unit[256]; /*!< data */ };

        //! table for double
        template <> struct ByteTo<double>
        { static const double      Unit[256]; /*!< data */};

        //! table for long double
        template <> struct ByteTo<long double>
        { static const long double Unit[256]; /*!< data */ };


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

            //! \param x unit floating point \return closest byte
            static inline uint8_t UnitToByte(const float &x) noexcept
            {
                return (uint8_t) floorf(x*256.0f + 0.5f);
            }

            //! \param x unit floating point \return closest byte
            static inline uint8_t UnitToByte(const double &x) noexcept
            {
                return (uint8_t) floor(x*256.0 + 0.5);
            }

            //! \param x unit floating point \return closest byte
            static inline uint8_t UnitToByte(const long double &x) noexcept
            {
                return (uint8_t) floorl(x*256.0L + 0.5L);
            }




            static const size_t  Count = 1 + 3*255; //!< r+g+b possilities
            static const uint8_t Table[Count];      //!< gray level from r+g+b

            //! \param r r \param g g \param b b \return 8-bits gray level
            static inline
            uint8_t ToByte(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return Table[ unsigned(r) + unsigned(g) + unsigned(b) ];
            }

            //! \param r r \param g g \param b b \return floating point gray level
            template <typename T> static inline
            T ToUnit(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return ByteTo<T>::Unit[ ToByte(r,g,b) ];
            }

            //! default color to gray conversion (floating point)
            template <typename T> struct To
            {

                //! \param r r \param g g \param b b \return floating point gray level
                static inline T Get(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
                {
                    return ToUnit<T>(r,g,b);
                }
            };

        };

        //! specialized color to 8-bits gray conversion
        template <> struct Gray::To<uint8_t>
        {
            //! \param r r \param g g \param b b \return 8-bits gray level
            static inline uint8_t Get(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return ToByte(r,g,b);
            }
        };
    }
}


#endif // !Y_Color_Gray_Included
