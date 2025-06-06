



//! \file

#ifndef Y_Concurrent_Singleton_BroadLockPolicy_Included
#define Y_Concurrent_Singleton_BroadLockPolicy_Included 1


#include "y/ability/lockable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Replica System Lock per class (Limited to Nucleus::Replicae)
    //
    //
    //__________________________________________________________________________
    class BroadLockPolicy
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit BroadLockPolicy();            //!< initialize
        virtual ~BroadLockPolicy() noexcept;   //!< cleanup

        //______________________________________________________________________
        //
        //
        // Policy
        //
        //______________________________________________________________________
        Lockable &access; //!< for global access

    private:
        Y_Disable_Copy_And_Assign(BroadLockPolicy); //!< disarding
    };


}

#endif


