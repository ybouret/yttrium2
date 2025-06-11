
#include "y/threading/single-threaded-class.hpp"

namespace Yttrium
{
    SingleThreadedClass::  SingleThreadedClass() noexcept {}
    SingleThreadedClass:: ~SingleThreadedClass() noexcept {}

    SingleThreadedClass:: Lock:: Lock(const SingleThreadedClass&) noexcept
    {
    }

    SingleThreadedClass:: Lock:: ~Lock() noexcept
    {
    }
    

}
