
//! \file

#ifndef Y_Color_Gray_Included
#define Y_Color_Gray_Included

#include "y/core/setup.hpp"

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
                static const T Unit[256]; //!< precomputed
            };


            
            static const size_t  Count = 1 + 3*255; //!< r+g+b possilities
            static const uint8_t Table[Count];      //!< grey levels

            //! \param r r \param g g \param b b \return grey level
            static inline
            uint8_t ToByte(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return Table[unsigned(r) + unsigned(g) + unsigned(b)];
            }

            //! \param r r \param g g \param b b \return floating point grey level
            template <typename T> static inline
            T ToFP(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
            {
                return ByteTo<T>::Table[ ToByte(r,g,b) ];
            }


        };

    }
}


#endif // !Y_Color_Gray_Included
