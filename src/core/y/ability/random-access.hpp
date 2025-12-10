

//! \file

#ifndef Y_Random_Access_Included
#define Y_Random_Access_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Random Access interface
    //
    //
    //__________________________________________________________________________
    class RandomAccess
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit RandomAccess() noexcept; //!< setup
    public:
        virtual ~RandomAccess() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void remove(const size_t) noexcept = 0; //!< remove item at given index

    private:
        Y_Disable_Copy_And_Assign(RandomAccess); //!< discarding
    };



}

#endif // !Y_Random_Access_Included

