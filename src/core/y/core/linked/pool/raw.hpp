
//! \file

#ifndef Y_Core_Linked_Pool_Raw_Included
#define Y_Core_Linked_Pool_Raw_Included 1

#include "y/core/linked/pool.hpp"
#include "y/ability/resettable.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! pool of "static" nodes
    //
    //
    //__________________________________________________________________________
    template <typename NODE>
    class RawPoolOf: public Core::PoolOf<NODE>, public Resettable
    {
    public:

        //! initialize
        inline explicit RawPoolOf() noexcept : Core::PoolOf<NODE>() {}

        //! cleanup
        inline virtual ~RawPoolOf() noexcept { reset_(); }


        inline virtual void reset() noexcept { reset_(); }

    private:
        Y_Disable_Copy_And_Assign(RawPoolOf); //!< discarding

        //! hard reset members
        inline void reset_() noexcept {
            Coerce(this->head) = 0;
            Coerce(this->size) = 0;
        }
    };

}

#endif

