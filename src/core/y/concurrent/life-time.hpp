//! \file

#ifndef Y_Concurrent_Life_Time_Included
#define Y_Concurrent_Life_Time_Included 1

#include "y/system/at-exit.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{

#define Y_LifeTime(NAME) NAME = __LINE__ - Initializer

    struct LifeTime
    {
        typedef System::AtExit::Longevity Longevity; //!< alias
        static const Longevity            GreatestLongevity = IntegerFor<Longevity>::Maximum; //!< reserved for ConcurrentNucleus
        enum { Initializer = __LINE__ + 1 };
        enum {
            Y_LifeTime(System)
        };
    };
}

#endif

