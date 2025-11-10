
#include "y/concurrent/api/pipeline/queue/squad.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Queue:: Squad:: Squad(const Site &site) :
        Object(),
        Leader(site->size()),
        waiting(),
        running(),
        pending(),
        garbage(),
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

        void Queue:: Squad:: flush() noexcept
        {
            Y_Lock(mutex);
            Y_Thread_Message("flush...");
            if(running.size>0)
                chief.wait(mutex);
        }


        void Queue:: Squad:: quit() noexcept
        {
            {
                Y_Lock(mutex);
                pending.release();
            }

            //------------------------------------------------------------------
            //
            // flush
            //
            //------------------------------------------------------------------
            flush();

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
            // LOCK mutex
            Y_Lock(mutex);
            for(Kernels::ConstIterator it=kernels.begin();it!=kernels.end();++it)
            {
                if( taskIDs.found(counter) )
                    throw Specific::Exception(CallSign,"multiple Task ID!!");

                // enqueue the counter
                taskIDs << counter;
                try
                {
                    // create task with the counter
                    pending.pushTail( new Task(*it,counter) );
                }
                catch(...)
                {
                    taskIDs.popTail(); // emergency removal of counter
                    throw;
                }

                // update counter
                ++counter;
            }

            // still locked => dispatch algorithm
            dispatch();

            // return: UNLOCK
        }

        void Queue:: Squad:: dispatch() noexcept
        {
            // called with a LOCKED mutex
            while(waiting.size && pending.size)
            {
                Worker * const worker = running.pushTail( waiting.popHead() );
                worker->task = pending.popHead();
                worker->resume();
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
        SUSPEND:
            worker.suspend();

            //------------------------------------------------------------------
            //
            // wake up on a LOCKED mutex
            //
            //------------------------------------------------------------------
            if(!worker.task)
                goto RETURN;

        PERFORM:
            assert(running.owns(&worker));

            // perform unlocked
            worker();


            // task is done, return LOCKED
            (void)garbage.pushTail(worker.task);
            worker.task = 0;

            if(pending.size>0)
            {
                // take next task
                worker.task = pending.popHead();
                goto PERFORM;
            }
            else
            {
                // back to suspend
                worker.task = 0;
                waiting.pushTail( running.pop( &worker) );
                if(running.size<=0)
                    chief.signal();
                goto SUSPEND;
            }


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
