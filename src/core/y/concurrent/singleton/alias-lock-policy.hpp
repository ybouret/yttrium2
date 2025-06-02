//! \file

#ifndef Y_Singleton_Alias_Lock_Policy_Included
#define Y_Singleton_Alias_Lock_Policy_Included 1

#include "y/ability/lockable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Alias to another access
    //
    //
    //__________________________________________________________________________
    template <typename SINGLETON>
    class AliasLockPolicy
    {
    public:
        //! setup
        inline explicit AliasLockPolicy() : access( SINGLETON::Instance().access ) {}

        //! cleanup
        inline virtual ~AliasLockPolicy() noexcept {}

        Lockable &access; //!< for aliased access

    private:
        Y_Disable_Copy_And_Assign(AliasLockPolicy); //!< disarding
    };


}


#endif

