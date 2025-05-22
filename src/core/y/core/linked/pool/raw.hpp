
//! \file

#ifndef Y_Core_Linked_Pool_Raw_Included
#define Y_Core_Linked_Pool_Raw_Included 1

#include "y/core/linked/pool.hpp"
#include "y/ability/resettable.hpp"

namespace Yttrium
{

    //! pool of "static" nodes
    template <typename NODE>
    class RawPoolOf: public Core::PoolOf<NODE>, public Resettable
    {
    public:
        inline explicit RawPoolOf() noexcept : Core::PoolOf<NODE>() {}
        inline virtual ~RawPoolOf() noexcept {}

        inline virtual void reset() noexcept
        {
            Coerce(this->head) = 0;
            Coerce(this->size) = 0;
        }

    private:
        Y_Disable_Copy_And_Assign(RawPoolOf);
    };

}

#endif

