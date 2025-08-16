

//! \file

#ifndef Y_Concurrent_Sole_Included
#define Y_Concurrent_Sole_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/concurrent/fake-lock.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Sole : public SIMD
        {
        public:
            static const char * const CallSign;

            explicit Sole() noexcept;
            virtual ~Sole() noexcept;

            virtual const char * callSign()       const noexcept;
            virtual void         operator()( Kernel & ) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Sole);
            FakeLock mutex;
            Context  context;
        };
    }

}

#endif
