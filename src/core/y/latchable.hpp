
//! \file

#ifndef Y_Latchable_Included
#define Y_Latchable_Included 1

#include "y/lockable.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Lockable and TryLock
    //
    //
    //__________________________________________________________________________
    class Latchable : public Lockable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Latchable() noexcept; //!< initialize
    public:
        virtual ~Latchable() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        
        //! try lock and update count
        /** \return success of operation */
        bool tryLock() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Latchable); //!< discarding

        //! do try lock
        /** \return success of operation*/
        virtual bool doTryLock() noexcept = 0;
    };

    //! helper for Latchable API
#define Y_Latchable_Decl() virtual bool doTryLock() noexcept
    
}

#endif

