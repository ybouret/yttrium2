
#include "y/concurrent/api/pipeline/task.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/thread/site.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/runnable.hpp"

#include "y/concurrent/thread/launch.hpp"

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
            Condition primary; //!< primary condition
            Condition replica; //!< replica condition
            Tasks     pending;
            Tasks     garbage;

        private:
            Y_Disable_Copy_And_Assign(Scheduler);
        };

        Scheduler:: Scheduler() :
        mutex(),
        primary(),
        replica(),
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
            bool             armed;
            Launch           launch;

        private:
            Y_Disable_Copy_And_Assign(Engine);
            void         quit() noexcept;
            Engine      &self() noexcept;
            virtual void run() noexcept;  //!< for agent
            virtual void loop() noexcept; //!< for engine
        };



        Engine:: Engine(const Site &site) :
        Scheduler(),
        size( site->size() ),
        agents(size),
        ready(0),
        armed(false),
        launch( self(), & Engine::loop )
        {

            // wait for loop() to be armed
            {
                Y_Lock(mutex);
                if(!armed) primary.wait(mutex);
                Y_Thread_Message("loop is armed");
            }

        }

        Engine & Engine:: self() noexcept { return *this; }

        void Engine:: loop() noexcept
        {
            // entering main loop
            mutex.lock();

            armed = true;
            primary.signal();

            Y_Thread_Message("loop is ok");

            // wait on the lock mutex
            replica.wait(mutex);

            // wake up on a locked mutex


            // return
            Y_Thread_Message("loop is done");
            mutex.unlock();

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

            // stop loop
            replica.signal();
        }

    }
}

using namespace Yttrium;

namespace
{

    class Something : public Concurrent:: Runnable
    {
    public:
        Something(const int a) : value(a) {}
        virtual ~Something() noexcept {}
        Something(const Something &_) : Runnable(), value(_.value) {}

        void compute() noexcept
        {
            Y_Thread_Message("<" << value << ">");

        }

        virtual void run() noexcept
        {
            compute();
        }

        int value;
    private:
        Y_Disable_Assign(Something);
    };

}

Y_UTEST(concurrent_q)
{

    Something              something(7);

    Concurrent::Engine engine( Concurrent::Site::Default );


}
Y_UDONE()

