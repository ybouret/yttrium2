
#include "y/concurrent/api/pipeline.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        
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
            Task::Dict::Iterator it = dict.begin();
            while(it != dict.end())
            {
                const Task::ID tid = Task::Dict::Cast<Task::ID>( *(it++) );
                switch( getUnlocked(tid) )
                {
                    case Task::CarriedOut: dict.remove(tid); continue;
                    case Task::InProgress:
                    case Task::Registered:
                        continue;
                }
            }
            return dict->size();
        }


    }

}
