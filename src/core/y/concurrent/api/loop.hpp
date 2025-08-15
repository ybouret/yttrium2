
//! \file

#ifndef Y_Concurrent_Loop_Included
#define Y_Concurrent_Loop_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Loop
        {
        protected:
            explicit Loop(const size_t);
        public:
            virtual ~Loop() noexcept;

            const size_t size;
        private:
            Y_Disable_Copy_And_Assign(Loop);
        };
    }

}

#endif

