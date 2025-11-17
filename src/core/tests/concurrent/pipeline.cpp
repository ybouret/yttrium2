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

Y_UTEST(concurrent_pipeline)
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



    Concurrent::TaskIDs  tids;
    

    Concurrent::Alone    stQ;
    std::cerr << "Enqueuing/Alone" << std::endl;
    stQ.enqueue(tids,klist);
    stQ.flush();
    tids.free();

    std::cerr << "Enqueuing/Queue" << std::endl;
    Concurrent::Queue    mtQ( Concurrent::Site::Default );
    mtQ.enqueue(tids,klist);
    mtQ.flush();





}
Y_UDONE()


