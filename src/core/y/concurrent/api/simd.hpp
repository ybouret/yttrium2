
//! \file

#ifndef Y_Concurrent_Loop_Included
#define Y_Concurrent_Loop_Included 1

#include "y/concurrent/api/parallel.hpp"
#include "y/concurrent/api/context.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class SIMD : public Parallel
        {
        public:
            static bool Verbose;
            typedef Functor<void,TL1(Context)> Kernel;

        protected:
            explicit SIMD(const size_t, const char * const);

        public:
            virtual ~SIMD() noexcept;

            virtual void operator()( Kernel & ) noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(SIMD);
        };

    }

}

#endif

