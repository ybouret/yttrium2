
//! \file

#ifndef Y_Latch_Included
#define Y_Latch_Included 1

#include "y/ability/lockable.hpp"


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
    class Latch : public Lockable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Latch() noexcept; //!< initialize
    public:
        virtual ~Latch() noexcept; //!< cleanup

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
        Y_Disable_Copy_And_Assign(Latch); //!< discarding

        //! do try lock
        /** \return success of operation*/
        virtual bool doTryLock() noexcept = 0;
    };

    //! helper for Latchable API
#define Y_Latchable_Decl() virtual bool doTryLock() noexcept
    
}

#endif

