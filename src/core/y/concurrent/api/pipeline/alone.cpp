

#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/pointer/auto.hpp"
#include "y/type/destroy.hpp"
#include "y/concurrent/fake-lock.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Alone:: CallSign = "Concurrent::Alone";

        class Alone:: Code : public Object
        {
        public:
            explicit Code() noexcept : fakeLock(), context(fakeLock,1,0)
            {
            }

            virtual ~Code() noexcept
            {
            }

            FakeLock      fakeLock;
            const Context context;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Alone:: Alone() :
        Pipeline(1,CallSign),
        code( new Code() )
        {
        }

        Alone:: ~Alone() noexcept
        {
            assert(code);
            Destroy(code);
        }

        const char * Alone:: callSign() const noexcept
        {
            return CallSign;
        }

        void Alone:: enqueueTask(Task * const task) noexcept
        {
            assert(0!=task);
            const AutoPtr<Task> guard(task);
            task->perform(code->context);
        }

        void Alone :: flush() noexcept
        {
            
        }

        void Alone :: purge() noexcept
        {

        }
        
        Task::Status Alone:: getUnlocked(const Task::ID) const noexcept
        {
            return Task::CarriedOut;
        }

        Lockable & Alone:: getLockable() const noexcept
        {
            return code->fakeLock;
        }

        void Alone:: enqueueBand(Task::Dict &,
                                 const Readable<Kernel> & todo)
        {
            const size_t n = todo.size();
            for(size_t i=1;i<=n;++i)
                enqueue( todo[i] );
        }
    }

}
