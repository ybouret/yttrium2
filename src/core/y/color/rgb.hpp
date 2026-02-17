//! \file

#ifndef Y_Color_RGB_Included
#define Y_Color_RGB_Included

#include "y/color/print.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Color
    {
        template <typename> class RGBA;

        //______________________________________________________________________
        //
        //
        //
        //! RGB scheme
        //
        //
        //______________________________________________________________________
        template <typename T>
        class RGB
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const size_t DIMENSIONS = 3; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup as black
            inline RGB() noexcept : r(0), g(0), b(0) {}

            //! setup \param R r \param G g \param B b
            inline RGB(const T R, const T G, const T B) noexcept : r(R), g(G), b(B) {}

            //! assign \param c another rgb \return *this
            inline RGB & operator=(const RGB &c) noexcept {
                r = c.r;
                g = c.g;
                b = c.b;
                return *this;
            }

            //! duplicate \param c another rgb
            inline  RGB(const RGB &c) noexcept : r(c.r), g(c.g), b(c.b) {}

            //! cleanup
            inline ~RGB() noexcept {}

            RGB(const RGBA<T> &c)              noexcept; //!< setup  \param c rgb
            RGB & operator=(const RGBA<T> & c) noexcept; //!< assign \param c rgb \return *this*

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline T &       operator[](const size_t i)       noexcept { assert(i>=1); assert(i<=3);  return *((&r)+i-1); } //!< \param i index \return access[1..2]
            inline const T & operator[](const size_t i) const noexcept { assert(i>=1); assert(i<=3);  return *((&r)+i-1); } //!< \param i index \return access[1..2]

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const RGB &c)
            {
                Print(os << '(',c.r) << ',';
                Print(os,c.g)        << ',';
                Print(os,c.b)        << ')';
                return os;
            }

            //! \param x first color \param y second color \return channel-wise equality
            inline friend bool operator==(const RGB &x, const RGB &y) noexcept
            {
                return (x.r == y.r) && (x.g == y.g) && (x.b == y.b);
            }

            //! \param x first color \param y second color \return channel-wise difference
            inline friend bool operator!=(const RGB &x, const RGB &y) noexcept
            {
                return (x.r != y.r) || (x.g != y.g) || (x.b != y.b);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T r; //!< red
            T g; //!< green
            T b; //!< blue
        };
    }
}


#endif // !Y_Color_RGB_Included
