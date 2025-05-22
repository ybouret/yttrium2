
//! \file

#ifndef Y_Releasable_Included
#define Y_Releasable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{
    class Releasable
    {
    protected:
        explicit Releasable() noexcept;

    public:
        virtual ~Releasable() noexcept;

        //! release all resources
        virtual void release() noexcept = 0;
        
    private:
        Y_Disable_Copy_And_Assign(Releasable);
    };

}

#endif

