
#include "y/color/gray.hpp"

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





    }

}

