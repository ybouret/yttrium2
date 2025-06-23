
#include "y/threading/multi-threaded-handle.hpp"

namespace Yttrium {

    MultiThreadedHandle::  MultiThreadedHandle( Lockable &handle ) noexcept : authorization( &handle)  {}
    MultiThreadedHandle:: ~MultiThreadedHandle() noexcept { Coerce(authorization) = 0; }
}
