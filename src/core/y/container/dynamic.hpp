
//! \file

#ifndef Y_DynamicContainer_Included
#define Y_DynamicContainer_Included 1

#include "y/container/gradual.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Dynamic Container interface
    //
    //
    //__________________________________________________________________________
    class DynamicContainer : public GradualContainer, public Releasable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit DynamicContainer() noexcept;
    public:
        virtual ~DynamicContainer() noexcept;

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! request extra space
        virtual void   reserve(const size_t) = 0;

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
        Y_Disable_Copy_And_Assign(DynamicContainer); //!< Discarding
    };

}

#endif

