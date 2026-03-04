#include "y/threading/global-multi-threaded.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium {

    GlobalMultiThreaded:: GlobalMultiThreaded() : authorization( & Lockable::Giant() ) {}
    GlobalMultiThreaded:: ~GlobalMultiThreaded() noexcept { Coerce(authorization) = 0; }

    GlobalMultiThreaded:: GlobalMultiThreaded(const GlobalMultiThreaded &_) noexcept : authorization(_.authorization) {}


}
