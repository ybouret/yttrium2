#include "y/concurrent/thread/site.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/api/kernel.hpp"
#include "y/container/cxx/series.hpp"
#include "y/core/linked/list/raw.hpp"

#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {



        class Worker : public Context
        {
        public:

            Worker(Mutex       &mx,
                   Condition   &cv,
                   const size_t sz,
                   const size_t rk,
                   size_t      &nt);
            ~Worker() noexcept;

            Mutex       & mutex;
            Condition   & chief;
            Condition     brake;
            Worker *      next;
            Worker *      prev;
            size_t      & done;
            Thread        impl;

        private:
            Y_Disable_Copy_And_Assign(Worker);
            static void Launch(void * const) noexcept;
            void        run() noexcept;
        };

        typedef RawListOf<Worker> Workers;

        Worker:: Worker(Mutex       &mx,
                        Condition   &cv,
                        const size_t sz,
                        const size_t rk,
                        size_t      &nt) :
        Context(mx,sz,rk),
        mutex(mx),
        chief(cv),
        brake(),
        next(0),
        prev(0),
        done(nt),
        impl(Launch,this)
        {
        }


        Worker:: ~Worker() noexcept
        {

        }

        void Worker:: Launch(void *const args) noexcept
        {
            assert(args);
            static_cast<Worker *>(args)->run();
        }

        void Worker:: run() noexcept
        {
            // initialize thread
            mutex.lock();
            assert(done==rank);

            // signal chief that we are ready
            ++done;
            chief.signal();


            // wait on a locked mutex
            Y_Thread_Message("ready @" << *this);
            brake.wait(mutex);


        }

        class Team
        {
        public:
            explicit Team(const Site &site);
            virtual ~Team() noexcept;

            const size_t      size;
            Mutex             mutex;
            Condition         chief;
            Workers           waiting;
            Workers           running;
            CxxSeries<Worker> workers;
            size_t            ready_;

        private:
            Y_Disable_Copy_And_Assign(Team);
            void quit() noexcept;

        };

        Team:: Team(const Site &site) :
        size(site->size()),
        mutex(),
        chief(),
        waiting(),
        running(),
        workers(size),
        ready_(0)
        {
            try {

                const size_t sz = size;
                for(size_t rk=0,wi=1;rk<size;++rk,++wi)
                {
                    workers.push(mutex,chief,sz,rk,ready_);
                    Y_Lock(mutex);
                    if(ready_<wi)
                        chief.wait(mutex);
                }
                Y_Thread_Message("all done");

                {
                    size_t wi = 1;
                    for(const PNode *node=(**site).head;node;node=node->next,++wi)
                    {
                        waiting.pushTail( &workers[wi] )->impl.assign(**node);
                    }
                }


            }
            catch(...)
            {
                quit();
                throw;
            }

        }

        void Team:: quit() noexcept
        {
        }


        Team:: ~Team() noexcept
        {
            quit();
        }




    }
}

using namespace Yttrium;

Y_UTEST(concurrent_q)
{
    Concurrent::Team team( Concurrent::Site::Default );
}
Y_UDONE()


