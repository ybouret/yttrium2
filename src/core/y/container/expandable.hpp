

//! \file

#ifndef Y_Expandable_Included
#define Y_Expandable_Included 1

#include "y/container/gradual.hpp"

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
    class Expandable : public Gradual
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Expandable() noexcept; //!< setup
    public:
        virtual ~Expandable() noexcept; //!< cleanup


        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void reserve(const size_t) = 0; //!< reserve more space

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void ensure(const size_t minCapacity); //!< reserve is necessary \param minCapacity capacity to reach

        //! \param currentCapacity should be size() \return argument for reserve
        static size_t NextIncrease(const size_t currentCapacity);

        //! \param currentCapacity should be size() \return minimal next capacity
        static size_t NextCapacity(const size_t currentCapacity);

    private:
        Y_Disable_Copy_And_Assign(Expandable); //!< discarding
    };

}

#endif
