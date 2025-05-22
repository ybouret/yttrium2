
//! \file

#ifndef Y_Resettable_Included
#define Y_Resettable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{
    class Resettable
    {
    protected:
        explicit Resettable() noexcept;

    public:
        virtual ~Resettable() noexcept;

        //! hard-reset state
        virtual void reset() noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Resettable);
    };

}

#endif

