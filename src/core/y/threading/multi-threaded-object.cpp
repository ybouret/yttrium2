#include "y/threading/multi-threaded-object.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium {

    MultiThreadedObject::  MultiThreadedObject() : authorization( new Concurrent::Mutex() ) {}
    MultiThreadedObject:: ~MultiThreadedObject() noexcept { Destroy(authorization); }
}
