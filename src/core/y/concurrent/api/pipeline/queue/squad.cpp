
#include "y/concurrent/api/pipeline/queue/squad.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Queue:: Squad:: Squad(const Site &site) :
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

        Queue::Squad:: ~Squad() noexcept
        {
            quit();
        }

        void Queue:: Squad:: quit() noexcept
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

        void Queue::Squad:: enqueue(TaskIDs       & taskIDs,
                                    const Kernels & kernels,
                                    Task::ID      & counter)
        {
            Y_Lock(mutex);
            for(Kernels::ConstIterator it=kernels.begin();it!=kernels.end();++it)
            {
                if( taskIDs.found(counter) )
                    throw Specific::Exception(CallSign,"multiple Task ID!!");

                // enqueue counter
                taskIDs << counter;
                try
                {
                    // create task
                    pending.pushTail( new Task(*it,counter) );
                }
                catch(...)
                {
                    taskIDs.popTail(); // emergency removal of coutner
                    throw;
                }

                // update counter
                ++counter;
            }
        }


        void Queue:: Squad:: run() noexcept
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
