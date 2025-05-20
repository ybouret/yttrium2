//! \file

#ifndef Y_System_AtExit_Included
#define Y_System_AtExit_Included 1


#include "y/core/setup.hpp"

//! Tunable AtExit Capacity
#if !defined(Y_System_AtExit_Capacity)
#  define Y_System_AtExit_Capacity 128
#endif

namespace Yttrium
{
    namespace System
    {
        //______________________________________________________________________
        //
        //
        //
        //! manage at exit functions with decreasing priorities
        //
        //
        //______________________________________________________________________
        struct AtExit
        {
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef uint16_t    Longevity;                             //!< alias
            typedef void      (*Function)(void *);                     //!< alias
            static const size_t Capacity = (Y_System_AtExit_Capacity); //!< internal queue size
            struct Code;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! register a new function to be performed
            /**
             \param func function to be called
             \param args func(args)
             \param life unique lifetime
             */
            static void Perform(Function        func,
                                void * const    args,
                                const Longevity life);
        };
    }
}

#endif

