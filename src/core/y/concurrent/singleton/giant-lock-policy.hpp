
//! \file

#ifndef Y_Concurrent_Singleton_GiantLockPolicy_Included
#define Y_Concurrent_Singleton_GiantLockPolicy_Included 1


#include "y/ability/lockable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Use giant lock for class access
    //
    //
    //__________________________________________________________________________
    class GiantLockPolicy
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit GiantLockPolicy();           //!< initialize
        virtual ~GiantLockPolicy() noexcept;  //!< cleanup

        //______________________________________________________________________
        //
        //
        // Policy
        //
        //______________________________________________________________________
        Lockable &access; //!< peristent giant lock

    private:
        Y_Disable_Copy_And_Assign(GiantLockPolicy); //!< cleanup
    };


}

#endif
