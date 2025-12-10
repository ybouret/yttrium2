//! \file

#ifndef Y_Color_RGB_Included
#define Y_Color_RGB_Included

#include "y/color/opaque.hpp"

namespace Yttrium
{
    namespace Color
    {

        template <typename T>
        class RGB
        {
        public:

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

            T r;
            T g;
            T b;
        };
    }
}


#endif // !Y_Color_RGB_Included
