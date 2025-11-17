
#include "y/concurrent/api/pipeline/task.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/thread/site.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/condition.hpp"


#include "y/utest/run.hpp"


namespace Yttrium
{
    namespace Concurrent
    {


        class Scheduler
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

        private:
            Y_Disable_Copy_And_Assign(Agent);
        };

        class Engine : public Scheduler
        {
        public:
            explicit Engine(const Site &site);
            virtual ~Engine() noexcept;

            const size_t     size;
            CxxSeries<Agent> agents;

        private:
            Y_Disable_Copy_And_Assign(Engine);
            void quit() noexcept;
        };

        Engine:: Engine(const Site &site) :
        Scheduler(),
        size( site->size() ),
        agents(size)
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

