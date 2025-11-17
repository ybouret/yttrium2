
#include "y/concurrent/api/pipeline/task.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/thread/site.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/runnable.hpp"


#include "y/utest/run.hpp"


namespace Yttrium
{
    namespace Concurrent
    {


        class Scheduler : public Runnable
        {
        public:
            explicit Scheduler();
            virtual ~Scheduler() noexcept;

            Mutex     mutex;
            Condition cv;
            Tasks     pending;
            Tasks     garbage;

        private:
            Y_Disable_Copy_And_Assign(Scheduler);
        };

        Scheduler:: Scheduler() :
        mutex(),
        cv(),
        pending(),
        garbage()
        {
        }

        Scheduler:: ~Scheduler() noexcept
        {

        }


        class Agent
        {
        public:
            explicit Agent(Scheduler &);
            virtual ~Agent() noexcept;

            Scheduler & sched;
            Condition   block;
            Thread      thread;

        private:
            Y_Disable_Copy_And_Assign(Agent);
        };

        Agent:: Agent(Scheduler &_) :
        sched(_),
        block(),
        thread(sched)
        {

        }

        Agent:: ~Agent() noexcept
        {

        }

        class Engine : public Scheduler
        {
        public:
            explicit Engine(const Site &site);
            virtual ~Engine() noexcept;

            const size_t     size;
            CxxSeries<Agent> agents;
            size_t           ready;

        private:
            Y_Disable_Copy_And_Assign(Engine);
            void quit() noexcept;
            virtual void run() noexcept;  //!< for agent
            //virtual void loop() noexcept; //!< for engine
        };

        Engine:: Engine(const Site &site) :
        Scheduler(),
        size( site->size() ),
        agents(size),
        ready(0)
        {
        }



        void Engine:: run() noexcept
        {

        }

        Engine:: ~Engine() noexcept
        {
            quit();
        }



        void Engine:: quit() noexcept
        {

        }

    }
}

using namespace Yttrium;

Y_UTEST(concurrent_q)
{

}
Y_UDONE()

