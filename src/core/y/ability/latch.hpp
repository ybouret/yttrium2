
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
        // Interface
        //
        //______________________________________________________________________
        
        //! try lock and update count
        /** \return success of operation */
        virtual bool tryLock() noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Latch); //!< discarding


    };


}

#endif // !Y_Latch_Included

