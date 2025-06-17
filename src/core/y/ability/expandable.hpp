

//! \file

#ifndef Y_Expandable_Included
#define Y_Expandable_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! able to reserve some items
    //
    //
    //__________________________________________________________________________
    class Expandable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Expandable() noexcept;
    public:
        virtual ~Expandable() noexcept;


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void reserve(const size_t) = 0;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        //! \param currentCapacity should be size() \return argument for reserve
        static size_t NextIncrease(const size_t currentCapacity);

        //! \param currentCapacity should be size() \return minimal next capacity
        static size_t NextCapacity(const size_t currentCapacity);

    private:
        Y_Disable_Copy_And_Assign(Expandable); //!< discarding
    };

}

#endif
