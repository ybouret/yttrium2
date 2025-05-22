
//! \file

#ifndef Y_Resettable_Included
#define Y_Resettable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Resettable interface
    //
    //
    //__________________________________________________________________________
    class Resettable
    {
    protected:
        explicit Resettable() noexcept; //!< setup

    public:
        virtual ~Resettable() noexcept; //!< cleanup

        //! hard-reset state
        virtual void reset() noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Resettable); //!< discarding
    };

}

#endif

