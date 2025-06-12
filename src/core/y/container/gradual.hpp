

//! \file

#ifndef Y_GradualContainer_Included
#define Y_GradualContainer_Included 1

#include "y/container.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Gradual Container  interface
    //
    //
    //__________________________________________________________________________
    class GradualContainer : public virtual Container
    {
    protected:
        explicit GradualContainer() noexcept;
    public:
        virtual ~GradualContainer() noexcept;

        virtual size_t capacity()  const noexcept = 0;
        virtual size_t available() const noexcept = 0;
        
    private:
        Y_Disable_Copy_And_Assign(GradualContainer);
    };

}

#endif

