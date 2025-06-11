
//! \file

#ifndef Y_Threading_Locker_Included
#define Y_Threading_Locker_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Threading
    {
        template <typename CLASS>
        class Locker
        {
        public:
            inline  Locker(const CLASS &obj) noexcept : host(Coerce(obj)) { obj.access->lock(); }
            inline ~Locker() noexcept { host.access->unlock(); }
        private:
            CLASS & host;
        };
    }
}

#endif

