#include "y/concurrent/thread/site.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/api/kernel.hpp"
#include "y/container/cxx/series.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/concurrent/runnable.hpp"


#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Leader : public Runnable
        {
        public:

            inline explicit Leader(const size_t sz) :
            mutex(), chief(), size(sz)
            {
            }


            inline virtual ~Leader() noexcept
            {
            }

            Mutex        mutex;
            Condition    chief;
            const size_t size;

        private:
            Y_Disable_Copy_And_Assign(Leader);
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
            next(0),
            prev(0),
            thread( Thread::Run<Leader>, &ld )
            {
            }

            Mutex     & mutex;
            Condition & chief;
            Condition   block;
            Worker    * next;
            Worker    * prev;
            Thread      thread;

        private:
            Y_Disable_Copy_And_Assign(Worker);
        };

        typedef RawListOf<Worker> Workers;

        class Brigade : public Leader
        {
        public:
            explicit Brigade(const Site site) :
            Leader(site->size()),
            waiting(),
            running(),
            workers(size),
            ready(0)
            {
                try {

                    const PNode *node = (**site).head;
                    for(size_t rk=0,wi=1;rk<size;++rk,++wi,node=node->next)
                    {
                        // start construction
                        workers.push(*this,rk);

                        // finish construction
                        Y_Lock(mutex);
                        if(ready<wi) chief.wait(mutex);
                        waiting.pushTail( &workers[wi] )->thread.assign( **node );
                    }



                }
                catch(...)
                {
                    quit();
                    throw;
                }
            }

            virtual ~Brigade() noexcept
            {
                quit();
            }

            Workers           waiting;
            Workers           running;
            CxxSeries<Worker> workers;
            size_t            ready;

        private:
            Y_Disable_Copy_And_Assign(Brigade);
            void quit() noexcept;

            virtual void run() noexcept;
        };


        void Brigade:: quit() noexcept
        {
            // flush

            // unleash waiting with no task
            std::cerr << "waiting = " << waiting.size << std::endl;
            assert(ready==waiting.size);
            while(waiting.size>0)
                waiting.popHead()->block.signal();

        }


        void Brigade:: run() noexcept
        {
            mutex.lock();


            // entering thread with LOCKED mutex
            assert(ready<size);
            Worker & worker = workers[++ready]; assert(worker.indx==ready);

            Y_Thread_Message("[+] " << worker);


            // signal chief that worker is ready
            chief.signal();

            // block worker on the LOCKED mutex
            worker.block.wait(mutex);

            // wake up on a LOCKED mutex


            // returning
            Y_Thread_Message("[-] " << worker);
            assert(ready>0);
            --ready;
            mutex.unlock();
        }



    }
}

using namespace Yttrium;

Y_UTEST(concurrent_q)
{
    Concurrent::Brigade q( Concurrent::Site::Default );
}
Y_UDONE()


