
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


        Task:: Batch:: ~Batch() noexcept
        {
            
        }

        Task:: Batch:: Batch(const size_t n) : CountedObject(), CxxSeries<Kernel>(n)
        {
        }
        

    }

}

