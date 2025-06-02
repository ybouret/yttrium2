//! \file

#ifndef Y_Container_Included
#define Y_Container_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    class Container
    {
    protected:
        explicit Container() noexcept;

    public:
        virtual ~Container() noexcept;

        virtual size_t size() const noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Container);
    };
}


#endif

