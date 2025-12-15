
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
    //! Low-level leap from lower to upper
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

        inline friend std::ostream & operator<<(std::ostream &os, const Leap &leap)
        {
            return os << leap.lower << "->" << leap.upper;
        }


        inline friend bool operator==(const Leap &lhs, const Leap &rhs) noexcept
        {
            return (lhs.lower == rhs.lower) && (lhs.upper==rhs.upper);
        }

        inline friend bool operator!=(const Leap &lhs, const Leap &rhs) noexcept
        {
            return (lhs.lower != rhs.lower) || (lhs.upper!=rhs.upper);
        }

        const T lower;
        const T upper;

    private:
        Y_Disable_Assign(Leap);

    };

}

#endif // !Y_MKL_Leap_Included
