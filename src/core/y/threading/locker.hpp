
//! \file

#ifndef Y_Threading_Locker_Included
#define Y_Threading_Locker_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Threading
    {

        //______________________________________________________________________
        //
        //
        //
        //! Lightweight locking mechanisment for host with access member
        //
        //
        //______________________________________________________________________
        template <typename CLASS>
        class Locker
        {
        public:
            //! store locked host \param obj object with access member
            inline  Locker(const CLASS &obj) noexcept : host(Coerce(obj)) { obj.access->lock(); }

            //! unlock host
            inline ~Locker() noexcept { host.access->unlock(); }
        private:
            CLASS & host; //!< PERSISTENT host
        };
    }
}

#endif

