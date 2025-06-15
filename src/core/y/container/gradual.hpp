

//! \file

#ifndef Y_GradualContainer_Included
#define Y_GradualContainer_Included 1

#include "y/container.hpp"
#include "y/ability/recyclable.hpp"

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
    class GradualContainer : public virtual Container, public Recyclable
    {
    protected:
        explicit GradualContainer() noexcept;
    public:
        virtual ~GradualContainer() noexcept;

        virtual size_t capacity()  const noexcept = 0; //!< current capacity
        virtual size_t available() const noexcept = 0; //!< current available space
        
    private:
        Y_Disable_Copy_And_Assign(GradualContainer);
    };

}

#endif

