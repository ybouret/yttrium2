

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
    class Gradual  : public virtual Container, public Recyclable
    {
    protected:
        explicit Gradual() noexcept; //!< setup
    public:
        virtual ~Gradual() noexcept; //!< cleanup

        virtual size_t capacity()  const noexcept = 0; //!< \return current capacity
        virtual size_t available() const noexcept = 0; //!< \return available space

    private:
        Y_Disable_Copy_And_Assign(Gradual); //!< discarding
    };

}

#endif

