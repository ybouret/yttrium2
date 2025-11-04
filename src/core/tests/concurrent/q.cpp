#include "y/concurrent/thread/site.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/api/kernel.hpp"
#include "y/container/cxx/series.hpp"

#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Leader
        {
        public:
            explicit Leader();
            virtual ~Leader() noexcept;

            Mutex     mutex;
            Condition synchronize;

        private:
            Y_Disable_Copy_And_Assign(Leader);
        };


        class Worker
        {
        public:

            Worker(Leader      &ll,
                   const size_t sz,
                   const size_t rk);
            ~Worker() noexcept;

            Leader &     leader;
            Context      context;
            Condition    linger;
            Thread       thread;

        private:
            Y_Disable_Copy_And_Assign(Worker);
            static void Launch(void * const) noexcept;
            void        run() noexcept;
        };

        Worker:: Worker(Leader &primary, const size_t sz, const size_t rk) :
        leader(primary),
        context(leader.mutex,sz,rk),
        linger(),
        thread(Launch,this)
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
            //------------------------------------------------------------------
            //
            // Entering thread : LOCK mutex
            //
            //------------------------------------------------------------------
            leader.mutex.lock();

            // suspend on LOCKED mutex
            linger.wait(leader.mutex);
        }

        class Team
        {
        public:
            explicit Team(const Site &site);
            virtual ~Team() noexcept;

            const size_t      size;
            CxxSeries<Worker> worker;

        private:
            Y_Disable_Copy_And_Assign(Team);
            void quit() noexcept;

        };

        Team:: Team(const Site &site) :
        size(site->size()),
        worker(size)
        {
            try {

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
        }




    }
}

using namespace Yttrium;

Y_UTEST(concurrent_q)
{

}
Y_UDONE()


