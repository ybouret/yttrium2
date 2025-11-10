
//! \file

#ifndef Y_Concurrent_Kernel_Included
#define Y_Concurrent_Kernel_Included 1

#include "y/concurrent/api/context.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //! High-Level Kernel function
        typedef Functor<void,TL1(Context)> Kernel;  

        //______________________________________________________________________
        //
        //
        //
        //! Kernel testing
        //
        //
        //______________________________________________________________________
        struct KernelTest
        {
            static void ST(Kernel &); //!< test in sequential environment
            static void MT(Kernel &); //!< test in one thread environment

        };

    }

}

#endif // !Y_Concurrent_Kernel_Included

