//! \file

#ifndef Y_Concurrent_Mutex_Included
#define Y_Concurrent_Mutex_Included 1

#include "y/ability/latch.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Mutex : public Latch
        {
        public:
            class Code;

            explicit Mutex();
            virtual ~Mutex() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Mutex);
            Code * const code;

            virtual bool doTryLock() noexcept;
            virtual void doLock()    noexcept;
            virtual void doUnlock()  noexcept;
        };
    }
}

#endif

