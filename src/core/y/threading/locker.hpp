
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
        //! Lightweight locking mechanisment for host with 'authorization' member
        //
        //
        //______________________________________________________________________
        template <typename CLASS>
        class Locker
        {
        public:
            //! store locked host \param obj object with 'access' member
            inline  Locker(const CLASS &obj) noexcept : host(Coerce(obj)) { obj.authorization->lock(); }

            //! unlock host
            inline ~Locker() noexcept { host.authorization->unlock(); }
        private:
            CLASS & host; //!< PERSISTENT host
        };
    }
}

#endif

