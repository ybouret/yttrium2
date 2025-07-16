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
            Y_LifeTime(SystemMemory)        /*!< for Memory::System          */,
            Y_LifeTime(DyadicMemory)        /*!< for Memory::Dyadic          */,
            Y_LifeTime(MemoryObjectLedger)  /*!< for Memory::Object::Ledger  */,
            Y_LifeTime(MemoryObjectBlocks ) /*!< for Memory::Object::Blocks  */,
            Y_LifeTime(MemoryQuanta)        /*!< for Memory::Quanta          */,
            Y_LifeTime(PooledMemory)        /*!< for Memory::Pooled          */,
            Y_LifeTime(ObjectFactory)       /*!< for Object::Factory         */,
            Y_LifeTime(IOChars)             /*!< for IO::Char                */,
            Y_LifeTime(ApexMemory)          /*!< for Apex::Archon            */,
            Y_LifeTime(LocalFS)             /*!< for  LocalFS                */
        };
    };
}

#endif

