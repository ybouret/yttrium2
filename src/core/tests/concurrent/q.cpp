
#include "y/concurrent/api/pipeline/task.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/thread/site.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/runnable.hpp"

#include "y/concurrent/thread/launch.hpp"
#include "y/type/copy-of.hpp"
#include "y/core/linked/list/raw.hpp"

#include "y/utest/run.hpp"


namespace Yttrium
{
    namespace Concurrent
    {


        class Scheduler : public Runnable
        {
        public:
            explicit Scheduler(const Site &site);
            virtual ~Scheduler() noexcept;

            const size_t size;       //!< number of threads
            Mutex        mutex;      //!< shared mutex
            Condition    primary;    //!< communication with primary
            Condition    replica;    //!< communication with replica
            Tasks        pending;    //!< pending tasks
            Tasks        garbage;    //!< garbage tasks

        private:
            Y_Disable_Copy_And_Assign(Scheduler);
        };

        Scheduler:: Scheduler(const Site &site) :
        size(site->size()),
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


        class Agent : public Context
        {
        public:
            explicit Agent(Scheduler &, const size_t rk);
            virtual ~Agent() noexcept;


            Scheduler & sched;  //!< persistent schedular
            Condition   block;  //!< local condition variable to suspend/resume
            Agent      *next;   //!< for list
            Agent      *prev;   //!< for list
            Thread      thread; //!< running thread

        private:
            Y_Disable_Copy_And_Assign(Agent);
        };

        typedef RawListOf<Agent> Agents;

        Agent:: Agent(Scheduler &_, const size_t rk) :
        Context(_.mutex,_.size,rk),
        sched(_),
        block(),
        next(0),
        prev(0),
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

            Agents           waiting;
            Agents           running;
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
        Scheduler(site),
        waiting(),
        running(),
        agents(size),
        ready(0),
        armed(false),
        launch( self(), & Engine::loop )
        {

            try
            {
                //--------------------------------------------------------------
                //
                // wait for loop() to be armed
                //
                //--------------------------------------------------------------
                {
                    Y_Lock(mutex);
                    if(!armed) primary.wait(mutex);
                    Y_Thread_Message("loop is armed");
                }
                launch.assign( **(**site).tail );

                //--------------------------------------------------------------
                //
                // construct synchronized agents
                //
                //--------------------------------------------------------------
                {
                    PNode *node = (**site).head;;
                    for(size_t i=1;i<=size;++i,node=node->next)
                    {
                        assert(ready<i);
                        agents.push(*this,ready);
                        {
                            Y_Lock(mutex);
                            if(ready<i) primary.wait(mutex);
                        }
                        // prepare and assign
                        waiting.pushTail( &agents[i] )->thread.assign(**node);
                    }
                }

            }
            catch(...)
            {
                quit();
                throw;
            }


        }

        Engine & Engine:: self() noexcept { return *this; }

        void Engine:: loop() noexcept
        {
            //------------------------------------------------------------------
            //
            // entering main loop
            //
            //------------------------------------------------------------------
            mutex.lock();

            armed = true;     // update status
            primary.signal(); // resume primary thread if waiting

            Y_Thread_Message("loop is ok");

            //------------------------------------------------------------------
            //
            // wait on the lock mutex
            //
            //------------------------------------------------------------------
            replica.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a locked mutex
            //
            //------------------------------------------------------------------


            //------------------------------------------------------------------
            //
            // return
            //
            //------------------------------------------------------------------
            Y_Thread_Message("loop is done");
            mutex.unlock();

        }

        void Engine:: run() noexcept
        {
            //------------------------------------------------------------------
            //
            // entering run agent
            //
            //------------------------------------------------------------------
            mutex.lock();

            assert(ready<size);
            Agent &agent = agents[++ready];
            assert(ready==agent.indx);
            Y_Thread_Message(agent << " is ready#" << ready);
            primary.signal();

            //------------------------------------------------------------------
            //
            // suspend on a LOCKED mutex
            //
            //------------------------------------------------------------------
            agent.block.wait(mutex);


            //------------------------------------------------------------------
            //
            // resume on a LOCKED mutex
            //
            //------------------------------------------------------------------


            //------------------------------------------------------------------
            //
            // returning
            //
            //------------------------------------------------------------------
            Y_Thread_Message(agent << " is done");
            --ready;
            mutex.unlock();
        }

        Engine:: ~Engine() noexcept
        {
            quit();
        }



        void Engine:: quit() noexcept
        {

            // prune/flush

            // stop agents
            assert(waiting.size==size);

            waiting.reset();
            running.reset();
            for(size_t i=size;i>0;--i)
            {
                agents[i].block.signal();
            }


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

