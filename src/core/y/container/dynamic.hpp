
//! \file

#ifndef Y_Dynamic_Included
#define Y_Dynamic_Included 1

#include "y/ability/collectable.hpp"
#include "y/container/expandable.hpp"

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
        inline explicit Dynamic() noexcept : Expandable(), Management() {}
    public:
        //! cleanup
        inline virtual ~Dynamic() noexcept {}

    private:
        Y_Disable_Copy_And_Assign(Dynamic); //!< Discarding
    };

}

#endif // !Y_Dynamic_Included

