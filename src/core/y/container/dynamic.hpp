
//! \file

#ifndef Y_DynamicContainer_Included
#define Y_DynamicContainer_Included 1

#include "y/container/gradual.hpp"
#include "y/ability/collectable.hpp"
#include "y/ability/expandable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Dynamic Container interface, Managment = Releasable | Collectable
    //
    //
    //__________________________________________________________________________
    template <typename Management>
    class Dynamic :
    public Gradual,
    public Expandable,
    public Management
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        //! setup
        inline explicit Dynamic() noexcept : Gradual(), Expandable(), Management() {}
    public:
        //! cleanup
        inline virtual ~Dynamic() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(Dynamic); //!< Discarding
    };

}

#endif

