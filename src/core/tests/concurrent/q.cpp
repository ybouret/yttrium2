#include "y/concurrent/thread/site.hpp"
#include "y/concurrent/api/pipeline/queue/worker.hpp"
#include "y/concurrent/api/pipeline/queue/squad.hpp"

#include "y/container/cxx/series.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/concurrent/runnable.hpp"


#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


#if 0
        class Squad : public Leader
        {
        public:
            typedef RawListOf<Worker> Workers;

            explicit Squad(const Site &site) :
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

            virtual ~Squad() noexcept;


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
                    ++counter;
                }
            }

            void dispatch() noexcept;



            Workers           waiting; //!< waiting workers
            Workers           running; //!< running workers
            Tasks             pending; //!< pending tasks
            CxxSeries<Worker> workers; //!< memory for workers
            size_t            ready;   //!< count sync

        private:
            Y_Disable_Copy_And_Assign(Squad);
            void quit() noexcept;

            virtual void run() noexcept;
        };
#endif

       
     


       



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


    std::cerr << "Create Kernels..." << std::endl;
    for(int i=1;i<=3;++i)
    {
        something.value = i;
        klist << something;
    }

    std::cerr << "Show Kernels..." << std::endl;
    for(Concurrent::Kernels::Iterator it=klist.begin();it!=klist.end();++it)
    {
        Concurrent::KernelTest::ST(*it);
    }

    std::cerr << "Enqueuing..." << std::endl;

    Concurrent::Queue::Squad q( Concurrent::Site::Default );

    Concurrent::TaskIDs  tids;
    Concurrent::Task::ID counter = 0;
    q.enqueue(tids,klist,counter);



}
Y_UDONE()


