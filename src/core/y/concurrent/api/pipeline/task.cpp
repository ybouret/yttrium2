
#include "y/concurrent/api/pipeline/task.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        Task:: ~Task() noexcept
        {
        }

        void Task:: perform(const Context &ctx) noexcept
        {
            Kernel &self = *this;
            try { self(ctx); } catch(...) { }
        }

        


    }

}

