//! \file

#ifndef Y_Core_Linked_List_Raw_Included
#define Y_Core_Linked_List_Raw_Included 1

#include "y/core/linked/list.hpp"
#include "y/ability/resettable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! list of "static" nodes
    //
    //
    //__________________________________________________________________________
    template <typename NODE>
    class RawListOf: public Core::ListOf<NODE>, public Resettable
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit RawListOf() noexcept : Core::ListOf<NODE>() {}

        //! cleanup
        inline virtual ~RawListOf() noexcept {}

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        inline virtual void reset() noexcept
        {
            Coerce(this->head) = 0;
            Coerce(this->tail) = 0;
            Coerce(this->size) = 0;
        }

    private:
        Y_Disable_Copy_And_Assign(RawListOf); //!< discarding
    };

}

#endif

