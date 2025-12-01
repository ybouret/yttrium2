
#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/concurrent/api/pipeline/invoke.hpp"


#include "y/utest/run.hpp"

#include "y/container/sequence/vector.hpp"



using namespace Yttrium;

namespace
{
    class Engine
    {
    public:

        explicit Engine()
        {
        }

        virtual ~Engine() noexcept
        {
        }

        template <typename T>
        inline void call(Lockable &sync, T & data)
        {
            {
                //Y_Giant_Lock();
                Y_Lock(sync);
                (std::cerr << "processing (" << data << ")" << std::endl).flush();
            }
        }


    private:
        Y_Disable_Copy_And_Assign(Engine);
    };
}

#include "y/random/park-miller.hpp"

Y_UTEST(concurrent_invoke)
{

    Random::ParkMiller         ran;
    Concurrent::Appliance      app = new Concurrent::Queue( Concurrent::Site::Default );
    Concurrent::Invoke<Engine> invoke( app );

#if 1
    int    iArg = 2;
    String sArg = "Hello";
    Concurrent::Invoke<Engine>::UnaryJob<int>    job1(invoke, & Engine::call<int>,     iArg);
    Concurrent::Invoke<Engine>::UnaryJob<String> job2(invoke, & Engine::call<String>,  sArg);
    Concurrent::Kernel  ker1(job1);
    Concurrent::Kernel  ker2(job2);

    Concurrent::KernelTest::ST(ker1);
    Concurrent::KernelTest::MT(ker2);

    Concurrent::TaskIDs taskIDs;
    {
        Vector<int> iVec;
        for(size_t i=ran.in<size_t>(10,20);i>0;--i)
        {
            iVec << ran.in<int>(1,100);
        }
        std::cerr << iVec << std::endl;

        invoke( &Engine::call<int>, taskIDs, iVec);
        app->flush();
    }

#endif


}
Y_UDONE()

