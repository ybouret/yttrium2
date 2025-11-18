
#include "y/concurrent/api/pipeline.hpp"

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



            Task      * task;       //!< task to perform
            Scheduler & scheduler;  //!< persistent schedular
            Condition   computing;  //!< local condition variable to suspend/resume
            Agent      *next;       //!< for list
            Agent      *prev;       //!< for list
            Thread      thread;     //!< running thread

        private:
            Y_Disable_Copy_And_Assign(Agent);
        };

        typedef RawListOf<Agent> Agents;

        Agent:: Agent(Scheduler  & sc,
                      const size_t rk) :
        Context(sc.mutex,sc.size,rk),
        task(0),
        scheduler(sc),
        computing(),
        next(0),
        prev(0),
        thread(scheduler)
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

            void prune() noexcept;
            void flush() noexcept;
            

            void         enqueue(TaskIDs       &taskIDs,
                                 const Kernels &kernels,
                                 Task::ID      &counter);

            Agents           waiting;
            Agents           running;
            CxxSeries<Agent> agents;
            size_t           ready;
            bool             armed;
            Launch           launch;

        private:
            Y_Disable_Copy_And_Assign(Engine);
            void          quit()     noexcept; //!< clean finish
            Engine      & self()     noexcept; //!< helper
            virtual void  run()      noexcept; //!< for agent
            virtual void  balance()  noexcept; //!< for engine
        };



        Engine:: Engine(const Site &site) :
        Scheduler(site),
        waiting(),
        running(),
        agents(size),
        ready(0),
        armed(false),
        launch( self(), & Engine::balance )
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
                // construct synchronized agents with run()
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
                        waiting.pushTail( &agents[i] )->thread.assign(**node);
                    }
                }

                //--------------------------------------------------------------
                //
                // ready!
                //
                //--------------------------------------------------------------
            }
            catch(...)
            {
                quit();
                throw;
            }


        }

        void Engine:: prune() noexcept
        {
            Y_Lock(mutex);
            pending.release();
            garbage.release();
        }


        void Engine:: flush() noexcept
        {
            Y_Lock(mutex);
            Y_Thread_Message("flushing pending #" << pending.size);
            garbage.release();
            if(running.size>0||pending.size>0)
                primary.wait(mutex);
            garbage.release();
            Y_Thread_Message("flushed!");
        }


        Engine & Engine:: self() noexcept { return *this; }

        void Engine:: balance() noexcept
        {
            //------------------------------------------------------------------
            //
            // entering main loop
            //
            //------------------------------------------------------------------
            mutex.lock();

            armed = true;     // update status
            primary.signal(); // resume primary thread if waiting

            Y_Thread_Message("loop is ready");

            //------------------------------------------------------------------
            //
            // wait on the LOCKED mutex
            //
            //------------------------------------------------------------------
        DISPATCH:
            replica.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a LOCKED mutex
            //
            //------------------------------------------------------------------
            if(pending.size>0)
            {
                //Y_Thread_Message("pending  =#" << pending.size);
                while(waiting.size>0 && pending.size>0)
                {
                    Agent * const agent = running.pushTail( waiting.popHead() );
                    agent->task = pending.popHead();
                    agent->computing.signal();
                }
                //Y_Thread_Message("remaining=#" << pending.size);
                goto DISPATCH;
            }

            //------------------------------------------------------------------
            //
            // else return
            //
            //------------------------------------------------------------------
            Y_Thread_Message("loop is returning");
            armed = false;
            mutex.unlock();

        }

        void Engine:: run() noexcept
        {
            //------------------------------------------------------------------
            //
            // entering run() for  agent
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
        SUSPEND:
            agent.computing.wait(mutex);


            //------------------------------------------------------------------
            //
            // resume on a LOCKED mutex
            //
            //------------------------------------------------------------------
            if(agent.task)
            {
                //Y_Thread_Message("running  @" << agent);
                assert(running.owns(&agent));

                //--------------------------------------------------------------
                //
                // perform unlocked task
                //
                //--------------------------------------------------------------
                {
                    mutex.unlock();
                    agent.task->perform(agent);
                    mutex.lock();
                }

                //--------------------------------------------------------------
                //
                // thrash task
                //
                //--------------------------------------------------------------
                garbage.pushHead(agent.task);
                agent.task = 0;

                //--------------------------------------------------------------
                //
                // update status
                //
                //--------------------------------------------------------------
                waiting.pushTail( running.pop( &agent) );
                //Y_Thread_Message("finished @" << agent);

                //--------------------------------------------------------------
                //
                // send signal according to state before going to SUSPEND
                //
                //--------------------------------------------------------------
                if(pending.size<=0)
                {

                    // no more work to do
                    if(running.size<=0)
                    {
                        // this was the last running
                        //Y_Thread_Message("signal primary all done");
                        primary.signal();
                    }

                }
                else
                {

                    // still go work to do
                    //Y_Thread_Message("still some work to do");
                    replica.signal();
                }



                goto SUSPEND;
            }

            //------------------------------------------------------------------
            //
            // returning from a LOCKED mutex (task==NULL)
            //
            //------------------------------------------------------------------
            Y_Thread_Message(agent << " is returning");
            --ready;
            mutex.unlock();
        }

        Engine:: ~Engine() noexcept
        {
            quit();
        }


        void Engine:: enqueue(TaskIDs       &taskIDs,
                              const Kernels &kernels,
                              Task::ID      &counter)
        {
            //------------------------------------------------------------------
            //
            // creating tasks in primary thread
            //
            //------------------------------------------------------------------
            Y_Lock(mutex);
            for(Kernels::ConstIterator it=kernels.begin();it!=kernels.end();++it)
            {
                if(taskIDs.found(counter)) throw Specific::Exception("TODO", "multiple task ID");
                taskIDs << counter;
                try { pending.pushTail( new Task(*it,counter) ); }
                catch(...) { taskIDs.popTail(); throw; }
                ++counter;
            }

            //------------------------------------------------------------------
            //
            // signal replica in loop() to dispatch and run
            //
            //------------------------------------------------------------------
            replica.signal();

        }


        void Engine:: quit() noexcept
        {
            prune();
            flush();

            // stop agents
            assert(waiting.size==size);

            waiting.reset();
            running.reset();
            for(size_t i=size;i>0;--i)
            {
                agents[i].computing.signal();
            }


            // stop loop
            replica.signal();
        }

    }
}

#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

static Writable<size_t> * track = 0;

namespace
{

    class Something
    {
    public:
        Something(const int a) : value(a), ran() {}
        ~Something() noexcept {}
        Something(const Something &_) : value(_.value), ran() {}

        void operator()(const Concurrent::Context &ctx)
        {
            Y_Thread_Message(value << " @" << ctx);
            volatile double sum = 0;
            for(size_t i = ran.in<size_t>(1000,1000000);i>0;--i)
            {
                sum += ran.to<double>();
            }
            if(track)
            {
                ++(*track)[ctx.indx];
            }
        }

        int                value;
        Random::ParkMiller ran;
    private:
        Y_Disable_Assign(Something);
    };

}

Y_UTEST(concurrent_q)
{

    Something          something(7);
    Concurrent::Engine engine( Concurrent::Site::Default );

    Concurrent::Kernels kernels;
    for(int i=1;i<=30;++i)
    {
        something.value = i;
        kernels << something;
    }

    Concurrent::TaskIDs  taskIDs;
    Concurrent::Task::ID counter = 0;
    Vector<size_t>       tracking(engine.size,0);
    track = & tracking;

    engine.enqueue(taskIDs,kernels,counter);
    engine.flush();

    std::cerr << "tracking=" << tracking << std::endl;



}
Y_UDONE()

