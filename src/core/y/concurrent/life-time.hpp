//! \file

#ifndef Y_Concurrent_Life_Time_Included
#define Y_Concurrent_Life_Time_Included 1

#include "y/system/at-exit.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{

    //! compute a named LifeTime
#define Y_LifeTime(NAME) NAME = GreatestLongevity - (__LINE__ - Initializer)

    //__________________________________________________________________________
    //
    //
    //
    //! Database of name LifeTimes for Singletons
    //
    //
    //__________________________________________________________________________
    struct LifeTimeOf
    {
        typedef System::AtExit::Longevity Longevity; //!< alias
        static const Longevity            GreatestLongevity = IntegerFor<Longevity>::Maximum; //!< reserved for ConcurrentNucleus
        enum { Initializer = __LINE__ + 1 /*!< preprocessor current line+skip */ };
        enum {
            Y_LifeTime(SystemMemory) /*!< for Memory::System */
        };
    };
}

#endif

