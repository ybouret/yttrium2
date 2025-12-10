
#include "y/color/gray.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Color
    {

#define Y_U(X) Y_F(X)/Y_F(255)


#define Y_F(X) X##.0f

        template <>
        const float Gray::ByteTo<float>::Table[256] =
        {
#include "gray.hxx"
        };


#undef  Y_F
#define Y_F(X) X##.0

        template <>
        const double Gray::ByteTo<double>::Table[256] =
        {
#include "gray.hxx"
        };


#undef  Y_F
#define Y_F(X) X##.0L

        template <>
        const long double Gray::ByteTo<long double>::Table[256] =
        {
#include "gray.hxx"
        };

        const uint8_t Gray:: Table[ Count ] =
        {
#include "gtab.hxx"
        };


        uint8_t Gray:: Get(const uint8_t r, const uint8_t g, const uint8_t b)
        {
            return Table[unsigned(r) + unsigned(g) + unsigned(b)];
        }
    }

}

