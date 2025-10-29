
//! \file

#ifndef Y_Lockable_Included
#define Y_Lockable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! (Recursive) Locking API
    //
    //
    //__________________________________________________________________________
    class Lockable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Lockable() noexcept;
    public:
        virtual ~Lockable() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void lock()   noexcept = 0; //!< lock object
        virtual void unlock() noexcept = 0; //!< unlock object

        //______________________________________________________________________
        //
        //
        // Method
        //
        //______________________________________________________________________
        static Lockable & Giant();      //!< \return Nucleus lock

    private:
        Y_Disable_Copy_And_Assign(Lockable);  //!< discarding
    };


    //__________________________________________________________________________
    //
    //
    //
    //! Scoped Lock
    //
    //
    //__________________________________________________________________________
    class ScopedLock
    {
    public:
        ScopedLock(Lockable &) noexcept; //!< setup by locking host
        ~ScopedLock()          noexcept; //!< unlock host
    private:
        Y_Disable_Copy_And_Assign(ScopedLock); //!< disacrding
        Lockable &host;                        //!< persistent host
    };

    //! create the guard name
#define Y_Lock__(X,Y) X##Y

    //! instantiate the guard name
#define Y_Lock_(HOST,ID) volatile Yttrium::ScopedLock Y_Lock__(__guard,ID)(HOST)

    //! use a local ScopedLock to lock HOST
#define Y_Lock(HOST) Y_Lock_(HOST,__LINE__)

    //! declare and use the giant lock
#define Y_Giant_Lock() static Yttrium::Lockable &giantLock = Yttrium::Lockable::Giant(); Y_Lock(giantLock)


}


#endif // !Y_Lockable_Included
