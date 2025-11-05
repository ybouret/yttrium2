
//! \file

#ifndef Y_Concurrent_Runnable_Included
#define Y_Concurrent_Runnable_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Runnable
        {
        protected:
            explicit Runnable() noexcept;

        public:
            virtual ~Runnable() noexcept;

            virtual void run() noexcept = 0;

        private:
            Y_Disable_Copy_And_Assign(Runnable);
        };
    }

}

#endif // !Y_Concurrent_Runnable_Included

