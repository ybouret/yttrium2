#include "y/concurrent/condition.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/api/pipeline/task.hpp"

#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Worker
        {

        public:

            explicit Worker(Mutex &     leaderMutex,
                            Condition & leaderComm);
            virtual ~Worker() noexcept;

            Task     *  task;
            Mutex    &  mutex; //!< leader mutex
            Condition   stop;
            Condition & comm;  //!< leader communication
            Thread      tool;
            Worker *    next;
            Worker *    prev;

        private:
            Y_Disable_Copy_And_Assign(Worker);
            static void Launch(void * const) noexcept;
            void        loop() noexcept;
        };


        void Worker:: Launch(void *const args) noexcept
        {
            assert(args);
            static_cast<Worker *>(args)->loop();
        }

        void Worker:: loop() noexcept
        {

        }

        Worker:: Worker(Mutex &     leaderMutex,
                        Condition & leaderComm) :
        task(0),
        mutex( leaderMutex ),
        stop(),
        comm(leaderComm),
        tool( Launch, this ),
        next(0),
        prev(0)
        {

        }


        Worker:: ~Worker() noexcept
        {

        }




    }

}

using namespace Yttrium;



Y_UTEST(concurrent_worker)
{

}
Y_UDONE()

