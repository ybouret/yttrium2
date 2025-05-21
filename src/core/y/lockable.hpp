
//! \file

#ifndef Y_Lockable_Included
#define Y_Lockable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{

    class Lockable
    {
    protected:
        explicit Lockable() noexcept;
    public:
        virtual ~Lockable() noexcept;


        void              lock()           noexcept;
        void              unlock()         noexcept;
        bool              isLocked() const noexcept;
        static Lockable & Giant();

        const size_t count;

    private:
        Y_Disable_Copy_And_Assign(Lockable);
        virtual void doLock()   noexcept = 0;
        virtual void doUnlock() noexcept = 0;
    };

#define Y_Lockable_Decl()               \
/**/  virtual void doLock()   noexcept; \
/**/  virtual void doUnlock() noexcept

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
        Y_Disable_Copy_And_Assign(ScopedLock);
        Lockable &host;
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


#endif
