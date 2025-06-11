#include "y/threading/global-multi-threaded.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium {

    GlobalMultiThreaded:: GlobalMultiThreaded() : access( & Lockable::Giant() ) {}
    GlobalMultiThreaded:: ~GlobalMultiThreaded() noexcept { Coerce(access) = 0; }
}
