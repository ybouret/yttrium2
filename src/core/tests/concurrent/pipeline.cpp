#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/thread.hpp"
#include "y/concurrent/fake-lock.hpp"
#include "y/random/park-miller.hpp"
#include "y/system/wall-time.hpp"

using namespace Yttrium;


namespace
{

    static double MaxWait = 0.1;

    class Something
    {
    public:

        Something(const int value) : a(value) {}
        ~Something() noexcept {}

        Something(const Something &_) : a(_.a)
        {

        }

        inline void routine(const Concurrent::Context &ctx)
        {
            const double ns = ran.to<double>() * MaxWait;
            Y_Thread_Message("a=" << a << " @" << ctx << " : " << ns);

        }

        inline void operator()(const Concurrent::Context &ctx)
        {
            routine(ctx);
        }

        int                a;
        Random::ParkMiller ran;

    private:
        Y_Disable_Assign(Something);
    };
}

Y_UTEST(concurrent_pipeline)
{



    Something         something(7);

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

    //stQ.enqueue(something);
    //stQ.flush();


    mtQ.enqueue(something);
    mtQ.flush();

    std::cerr << std::endl;
    std::cerr << "...Done!" << std::endl;
}
Y_UDONE()
