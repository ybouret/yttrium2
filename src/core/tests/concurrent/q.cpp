#include "y/concurrent/thread/site.hpp"
//#include "y/concurrent/api/pipeline/queue/worker.hpp"
#include "y/concurrent/api/pipeline/queue/squad.hpp"

#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/concurrent/api/pipeline/alone.hpp"


#include "y/utest/run.hpp"


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
            (std::cerr << "exec @" << ctx << " => " << value << std::endl).flush();

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
    for(int i=1;i<=30;++i)
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

    q.flush();




}
Y_UDONE()


