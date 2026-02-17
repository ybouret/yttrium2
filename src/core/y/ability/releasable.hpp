
//! \file

#ifndef Y_Releasable_Included
#define Y_Releasable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Releasable interface
    //
    //
    //__________________________________________________________________________
    class Releasable
    {
    protected:
        explicit Releasable() noexcept; //!< setup

    public:
        virtual ~Releasable() noexcept; //!< cleanup

        //! release all resources
        virtual void release() noexcept = 0;
        
    private:
        Y_Disable_Copy_And_Assign(Releasable); //!< discarding
    };

}

#endif // !Y_Releasable_Included

