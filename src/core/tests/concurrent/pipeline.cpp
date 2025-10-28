#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/thread.hpp"
#include "y/concurrent/fake-lock.hpp"

using namespace Yttrium;


namespace
{
    class Something
    {
    public:

        Something(const int value) : a(value) {}
        ~Something() noexcept {}

        Something(const Something &_) : a(_.a)
        {

        }

        inline void operator()(const Concurrent::Context &ctx)
        {
            Y_Thread_Message("a=" << a << " @" << ctx);
        }

        int a;


    private:
        Y_Disable_Assign(Something);
    };
}

Y_UTEST(concurrent_pipeline)
{
    {
        Concurrent::Alone stQ;
        Concurrent::Queue mtQ(Concurrent::Site::Default);
    }

    Concurrent::Tasks tasks;
    Something         something(7);
    tasks.pushTail( new Concurrent::Task(something,1) );

    Concurrent::FakeLock       fakeLock;
    const Concurrent::Context  seq(fakeLock,1,0);

    something.a += 2;
    something(seq);
    (*tasks.tail)(seq);


}
Y_UDONE()
