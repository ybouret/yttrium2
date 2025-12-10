
//! \file

#ifndef Y_Color_RGBA_Included
#define Y_Color_RGBA_Included

#include "y/color/opaque.hpp"
#include "y/color/print.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Color
    {

        template <typename> class RGB;

        template <typename T>
        class RGBA
        {
        public:
            static const size_t DIMENSIONS = 4; //!< alias

            inline RGBA() noexcept : r(0), g(0), b(0), a(0) {}
            inline RGBA(const T R, const T G, const T B, const T A = Opaque<T>::Value) noexcept : r(R), g(G), b(B), a(A) {}

            inline RGBA & operator=(const RGBA &c) noexcept {
                r = c.r;
                g = c.g;
                b = c.b;
                a = c.a;
                return *this;
            }
            inline  RGBA(const RGBA &c) noexcept : r(c.r), g(c.g), b(c.b), a(c.a) {}
            inline ~RGBA() noexcept {}

            inline T &       operator[](const size_t i)       noexcept { assert(i>=1); assert(i<=4);  return *((&r)+i-1); } //!< \param i index \return access[1..2]
            inline const T & operator[](const size_t i) const noexcept { assert(i>=1); assert(i<=4);  return *((&r)+i-1); } //!< \param i index \return access[1..2]

            

            inline friend std::ostream & operator<<(std::ostream &os, const RGBA &c)
            {
                Print(os << '(',c.r) << ',';
                Print(os,c.g)        << ',';
                Print(os,c.b)        << ',';
                Print(os,c.a)        << ')';
                return os;
            }

            RGBA(const RGB<T> &, const T = Opaque<T>::Value) noexcept; //!< setup from rgb
            RGBA & operator=(const RGB<T> &)                 noexcept; //!< assign r,g,b


            T r;
            T g;
            T b;
            T a;
        };
    }
}


#endif // !Y_Color_RGBA_Included
