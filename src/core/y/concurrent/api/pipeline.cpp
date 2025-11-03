
#include "y/concurrent/api/pipeline.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //bool SIMD::Verbose = false;

        Pipeline:: Pipeline(const size_t n, const char * const id) :
        Parallel(n,id),
        counter(0)
        {
        }

        Pipeline:: ~Pipeline() noexcept
        {
        }


        void Pipeline:: batch(Task::Dict &dict, const Batch &todo)
        {
            enqueueBand(dict,*todo);
        }

        Task::Status Pipeline:: query(const Task::ID tid) const noexcept
        {
            Y_Lock( getLockable() );
            return getUnlocked(tid);
        }

        size_t Pipeline:: prune(Task::Dict &dict) const noexcept
        {

            Y_Lock( getLockable() );

            
            return dict->size();
        }


    }

}
