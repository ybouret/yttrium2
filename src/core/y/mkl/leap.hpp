
//! \file

#ifndef Y_MKL_Leap_Included
#define Y_MKL_Leap_Included 1

#include "y/core/setup.hpp"
#include <iostream>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! 2D Vertex
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Leap
    {
    public:

        inline explicit Leap(const T lo, const T up) noexcept :
        lower(lo),
        upper(up)
        {
        }

        inline virtual ~Leap() noexcept {}

        inline Leap(const Leap &leap) noexcept :
        lower(leap.lower),
        upper(leap.upper)
        {

        }

        inline Leap & operator=(const Leap &leap) noexcept
        {
            lower = leap.lower;
            upper = leap.upper;
            return *this;
        }

        inline friend std::ostream & operator<<(std::ostream &os, const Leap &leap)
        {
            return os << leap.lower << "->" << leap.upper;
        }


        T lower;
        T upper;

    };

}

#endif // !Y_MKL_Leap_Included
