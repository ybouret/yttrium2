#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/thread.hpp"
#include "y/concurrent/fake-lock.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/cxx/series.hpp"

#include <cmath>

using namespace Yttrium;


namespace
{

    static Writable<size_t> *target = 0;

    class Something
    {
    public:

        Something(const int value) : a(value), sum(0), ran() {}
        ~Something() noexcept {}

        Something(const Something &_) : a(_.a), sum(0), ran()
        {

        }

        inline void routine(const Concurrent::Context &ctx)
        {
            Y_Thread_Message("\ta=" << a << " @" << ctx);
            sum = 0;
            for(size_t i=ran.leq<size_t>(10000);i>0;--i)
            {
                const double c = std::cos( 3.14 * ran.to<double>() );
                sum += c*c;
            }
            if(target) (*target)[ctx.indx]++;
        }

        inline void operator()(const Concurrent::Context &ctx)
        {
            routine(ctx);
        }

        int                a;
        double             sum;
        Random::ParkMiller ran;

    private:
        Y_Disable_Assign(Something);
    };
}

Y_UTEST(concurrent_pipeline)
{

#if 0
    Something         something(7);
    Vector<size_t>    scatter;

    {
        Concurrent::Tasks tasks;
        tasks.pushTail( new Concurrent::Task(something,1) );

        Concurrent::FakeLock       fakeLock;
        const Concurrent::Context  seq(fakeLock,1,0);

        something.a += 2;
        something(seq);
        (*tasks.tail)(seq);
        tasks.pushTail( new Concurrent::Task(something, & Something::routine, 2) );
        (*tasks.tail)(seq);

        something.a -= 4;
        Concurrent::Kernel k(something);
        k(seq);
        tasks.pushTail( new Concurrent::Task(k,3) );
        (*tasks.tail)(seq);
    }

    std::cerr << std::endl;
    std::cerr << "Using Pipelines..." << std::endl;

    something.a = 7;

    Concurrent::Alone stQ;
    Concurrent::Queue mtQ(Concurrent::Site::Default);

    scatter.adjust(mtQ.size,0);
    scatter.ld(0);
    target = &scatter;

    for(int n=0;n<=100;++n)
    {
        (std::cerr << "---- n=" << n <<  " ----" << std::endl).flush();
        for(int i=1;i<=n;++i)
        {
            something.a = i;
            mtQ.enqueue(something);
        }
        mtQ.flush();
    }

    std::cerr << std::endl;
    std::cerr << "...Done!" << std::endl;
    std::cerr << "scatter=" << scatter << std::endl;

    std::cerr << std::endl;
    std::cerr << "Using Batch..." << std::endl;

    DataBook<>::PoolType   pool;
    Concurrent::Task::Dict dict(pool);
    {
        const int n = 100;
        scatter.ld(0);
        Concurrent::Batch batch = new Concurrent::Task::Batch(n);
        for(int i=1;i<=n;++i)
        {
            something.a = i;
            (*batch) << something;
        }

        stQ.batch(dict,batch);
        stQ.flush();

        dict.free();
        mtQ.batch(dict,batch);



        mtQ.flush();


    }
#endif

}
Y_UDONE()
