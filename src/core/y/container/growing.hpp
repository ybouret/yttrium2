


//! \file

#ifndef Y_GrowingContainer_Included
#define Y_GrowingContainer_Included 1

#include "y/container/gradual.hpp"
#include "y/ability/expandable.hpp"

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
    class Growing  : public  Gradual, public Expandable
    {
    protected:
        explicit Growing() noexcept; //!< setup
    public:
        virtual ~Growing() noexcept; //!< cleanup



    private:
        Y_Disable_Copy_And_Assign(Growing); //!< discarding
    };

}

#endif

