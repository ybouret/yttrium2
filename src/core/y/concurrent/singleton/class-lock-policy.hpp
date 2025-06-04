

//! \file

#ifndef Y_Concurrent_Singleton_ClassLockPolicy_Included
#define Y_Concurrent_Singleton_ClassLockPolicy_Included 1


#include "y/concurrent/mutex.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! One Lock (Mutex) per class
    //
    //
    //__________________________________________________________________________
    class ClassLockPolicy
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit ClassLockPolicy();           //!< initialize
        virtual ~ClassLockPolicy() noexcept;  //!< cleanup

        //______________________________________________________________________
        //
        //
        // Policy
        //
        //______________________________________________________________________
        Concurrent::Mutex access; //!< for local access

    private:
        Y_Disable_Copy_And_Assign(ClassLockPolicy); //!< discarding
    };


}

#endif
