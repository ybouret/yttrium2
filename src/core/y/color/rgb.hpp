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

        template <typename T>
        class RGB
        {
        public:
            static const size_t DIMENSIONS = 3; //!< alias

            inline RGB() noexcept : r(0), g(0), b(0) {}
            inline RGB(const T R, const T G, const T B) noexcept : r(R), g(G), b(B) {}

            inline RGB & operator=(const RGB &c) noexcept {
                r = c.r;
                g = c.g;
                b = c.b;
                return *this;
            }
            inline  RGB(const RGB &c) noexcept : r(c.r), g(c.g), b(c.b) {}
            inline ~RGB() noexcept {}

            RGB(const RGBA<T> &)             noexcept; //!< setup from rgba
            RGB & operator=(const RGBA<T> &) noexcept; //!< assign r,g,b

            inline T &       operator[](const size_t i)       noexcept { assert(i>=1); assert(i<=3);  return *((&r)+i-1); } //!< \param i index \return access[1..2]
            inline const T & operator[](const size_t i) const noexcept { assert(i>=1); assert(i<=3);  return *((&r)+i-1); } //!< \param i index \return access[1..2]

            inline friend std::ostream & operator<<(std::ostream &os, const RGB &c)
            {
                Print(os << '(',c.r) << ',';
                Print(os,c.g)        << ',';
                Print(os,c.b)        << ')';
                return os;
            }

            T r;
            T g;
            T b;
        };
    }
}


#endif // !Y_Color_RGB_Included
