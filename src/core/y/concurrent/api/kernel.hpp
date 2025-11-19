
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

            //! test in one thread environment
            /**
             \param sz assumed number of threads
             \param rk assume rank in threads
             */
            static void MT(Kernel &, const size_t sz=1, const size_t rk=0);

        };

    }

}

#endif // !Y_Concurrent_Kernel_Included

