
//! \file

#ifndef Y_Threading_Locker_Included
#define Y_Threading_Locker_Included 1

#include "y/core/setup.hpp"
#include "y/threading/must-lock.hpp"
#include <cassert>

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
            inline  Locker(const CLASS &obj) noexcept : host(Coerce(obj))
            {
                assert(host.authorization);
                host.authorization->lock();
            }

            //! unlock host
            inline ~Locker() noexcept
            {
                assert(host.authorization);
                host.authorization->unlock();
            }
            
        private:
            Y_Disable_Copy_And_Assign(Locker);
            CLASS & host; //!< PERSISTENT host
        };
    }
}

#endif

