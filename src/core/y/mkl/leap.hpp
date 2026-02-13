
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
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup unchecked \param lo lower bound \param up upper bound
        inline explicit Leap(const T lo, const T up) noexcept :
        lower(lo),
        upper(up)
        {
        }

        //! cleanup
        inline virtual ~Leap() noexcept {}

        //! duplicate \param leap another leap
        inline Leap(const Leap &leap) noexcept :
        lower(leap.lower),
        upper(leap.upper)
        {

        }

        //! display
        inline friend std::ostream & operator<<(std::ostream &os, const Leap &leap)
        {
            return os << leap.lower << "->" << leap.upper;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \param lhs lhs \param rhs rhs \return equality
        inline friend bool operator==(const Leap &lhs, const Leap &rhs) noexcept
        {
            return (lhs.lower==rhs.lower) && (lhs.upper==rhs.upper);
        }

        //! \param lhs lhs \param rhs rhs \return difference
        inline friend bool operator!=(const Leap &lhs, const Leap &rhs) noexcept
        {
            return (lhs.lower != rhs.lower) || (lhs.upper!=rhs.upper);
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const T lower; //!< lower bound
        const T upper; //!< upper bound

    private:
        Y_Disable_Assign(Leap); //!< discarding

    };

}

#endif // !Y_MKL_Leap_Included
