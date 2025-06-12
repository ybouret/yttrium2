
//! \file

#ifndef Y_DynamicContainer_Included
#define Y_DynamicContainer_Included 1

#include "y/container.hpp"

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
    class DynamicContainer : public Container
    {
    protected:
        explicit DynamicContainer() noexcept;
    public:
        virtual ~DynamicContainer() noexcept;

        virtual size_t capacity()  const noexcept = 0;
        virtual size_t available() const noexcept = 0;
        virtual void   reserve(const size_t) = 0;

    private:
        Y_Disable_Copy_And_Assign(DynamicContainer);
    };

}

#endif

