
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/utest/run.hpp"





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
            {
                Y_Lock(ctx.sync);
                (std::cerr << value << " @" << ctx << std::endl).flush();
            }
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

    Concurrent::Queue   Q( Concurrent::Site::Default );
    Concurrent::Kernels kernels;
    for(int i=1;i<=30;++i)
    {
        kernels << Something(i);
    }

    Concurrent::TaskIDs  taskIDs;

    //Concurrent::Task::ID counter = 0;
    Vector<size_t> tracking(Q.size,0);
    track = & tracking;

    Q.enqueue(taskIDs,kernels);
    Q.flush();

    std::cerr << "tracking=" << tracking << std::endl;



}
Y_UDONE()

