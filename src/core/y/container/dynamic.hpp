
//! \file

#ifndef Y_DynamicContainer_Included
#define Y_DynamicContainer_Included 1

#include "y/container/gradual.hpp"

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
    class DynamicContainer : public GradualContainer
    {
    protected:
        explicit DynamicContainer() noexcept;
    public:
        virtual ~DynamicContainer() noexcept;

        virtual void   reserve(const size_t) = 0;

        static size_t NextCapacity(const size_t currentCapacity);
        static size_t NextIncrease(const size_t currentCapacity);
        
    private:
        Y_Disable_Copy_And_Assign(DynamicContainer);
    };

}

#endif

