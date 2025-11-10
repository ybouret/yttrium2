#include "y/concurrent/thread/site.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/api/pipeline.hpp"

#include "y/container/cxx/series.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/concurrent/runnable.hpp"


#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        

        //______________________________________________________________________
        //
        //
        //
        // Necessary to initialize worker
        //
        //
        //______________________________________________________________________
        class Leader : public Runnable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit Leader(const size_t sz) :
            mutex(), chief(), size(sz)
            {
            }



            inline virtual ~Leader() noexcept
            {
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Mutex        mutex; //!< common mutes
            Condition    chief; //!< communication condition
            const size_t size;  //!< number of workers to build

        private:
            Y_Disable_Copy_And_Assign(Leader); //!< discarding
        };

        class Worker : public Context
        {
        public:

            inline explicit Worker(Leader &     ld,
                                   const size_t rk) :
            Context(ld.mutex,ld.size,rk),
            mutex(ld.mutex),
            chief(ld.chief),
            block(),
            task(0),
            next(0),
            prev(0),
            thread( Thread::Run<Leader>, &ld )
            {
            }

            Mutex     & mutex;
            Condition & chief;
            Condition   block;
            Task *      task;
            Worker    * next;
            Worker    * prev;
            Thread      thread;

        private:
            Y_Disable_Copy_And_Assign(Worker);
        };


        class Brigade : public Leader
        {
        public:
            typedef RawListOf<Worker> Workers;

            explicit Brigade(const Site &site) :
            Leader(site->size()),
            waiting(),
            running(),
            pending(),
            workers(size),
            ready(0)
            {
                try {

                    const PNode *node = (**site).head;
                    for(size_t rk=0,wi=1;rk<size;++rk,++wi,node=node->next)
                    {
                        // start worker construction
                        workers.push(*this,rk);

                        // finish worker construction and assign it
                        Y_Lock(mutex);
                        if(ready<wi)
                            chief.wait(mutex);
                        waiting.pushTail( &workers[wi] )->thread.assign( **node );
                    }

                }
                catch(...)
                {
                    quit();
                    throw;
                }
            }

            virtual ~Brigade() noexcept;


            void enqueue(TaskIDs       & taskIDs,
                         const Kernels & kernels,
                         Task::ID      & counter)
            {
                Y_Lock(mutex);
                for(Kernels::ConstIterator it=kernels.begin();it!=kernels.end();++it)
                {
                    if( taskIDs.found(counter) )
                        throw Specific::Exception("blabla","multiple Task ID!!");
                    taskIDs << counter;
                    try
                    {
                        pending.pushTail( new Task(*it,counter) );
                    }
                    catch(...)
                    {
                        taskIDs.popTail();
                        throw;
                    }
                }
            }

            Workers           waiting; //!< waiting workers
            Workers           running; //!< running workers
            Tasks             pending; //!< pending tasks
            CxxSeries<Worker> workers; //!< memory for workers
            size_t            ready;   //!< count sync

        private:
            Y_Disable_Copy_And_Assign(Brigade);
            void quit() noexcept;

            virtual void run() noexcept;
        };

        Brigade:: ~Brigade() noexcept
        {
            quit();
        }

        void Brigade:: quit() noexcept
        {
            //------------------------------------------------------------------
            //
            // flush
            //
            //------------------------------------------------------------------


            //------------------------------------------------------------------
            //
            // unleash waiting with no task, no control, wait for threads to end
            //
            //------------------------------------------------------------------
            std::cerr << "waiting = " << waiting.size << std::endl;
            assert(ready==waiting.size);

            while(waiting.size>0)
                waiting.popHead()->block.signal();


        }


        void Brigade:: run() noexcept
        {
            mutex.lock();

            //------------------------------------------------------------------
            //
            // entering thread with LOCKED mutex
            //
            //------------------------------------------------------------------
            assert(ready<size);
            Worker & worker = workers[++ready]; assert(worker.indx==ready);

            Y_Thread_Message("[+] " << worker);


            // signal chief that worker is ready
            chief.signal();

            //------------------------------------------------------------------
            //
            // block worker on the LOCKED mutex
            //
            //------------------------------------------------------------------
            worker.block.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a LOCKED mutex
            //
            //------------------------------------------------------------------
            if(!worker.task)
                goto RETURN;

            assert(waiting.owns(&worker));


            //------------------------------------------------------------------
            //
            // returning
            //
            //------------------------------------------------------------------
        RETURN:
            Y_Thread_Message("[-] " << worker);
            assert(ready>0);
            --ready;
            mutex.unlock();
        }



    }

}

using namespace Yttrium;

namespace
{
    class Something
    {
    public:

        inline Something(const int arg) : value(arg)
        {
        }


        inline ~Something() noexcept
        {
        }

        inline Something(const Something &_) : value(_.value)
        {
        }

        void operator()(const Concurrent::Context &ctx)
        {
            Y_Lock(ctx.sync);
            (std::cerr << ctx << " => " << value << std::endl).flush();

        }



        int value;

    private:
        Y_Disable_Assign(Something);
    };
}

Y_UTEST(concurrent_q)
{
    Concurrent::Kernels klist;
    Something           something(7);
    klist.pushTail(something);
    for(Concurrent::Kernels::Iterator it=klist.begin();it!=klist.end();++it)
    {
        Concurrent::KernelTest::ST(*it);
    }

    {
        Concurrent::Brigade q( Concurrent::Site::Default );
    }



}
Y_UDONE()


