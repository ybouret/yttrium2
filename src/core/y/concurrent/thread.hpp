//! \file

#ifndef Y_Concurrent_Mutex_Included
#define Y_Concurrent_Mutex_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


        class Thread
        {
        public:
            class Code;
            typedef void (*Proc)(void * const);
            explicit Thread(Proc proc, void * const args);
            virtual ~Thread() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Thread);
            Code * const code;
        };


    }

}

#endif

