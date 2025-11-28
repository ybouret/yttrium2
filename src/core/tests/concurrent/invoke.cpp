
#include "y/concurrent/api/pipeline.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"


#include "y/utest/run.hpp"

#include "y/pointer/arc.hpp"
#include "y/container/sequence/vector.hpp"


namespace Yttrium
{
    namespace Concurrent
    {
        typedef ArcPtr<Pipeline> Appliance;

        template <typename ENGINE>
        class Asynchronous
        {
        public:

            // Node containing engine
            class ENode : public Object
            {
            public:
                template <typename ARG>
                inline explicit ENode(ARG &arg) : Object(), engine(arg) {}
                inline explicit ENode()         : Object(), engine()    {}
                inline virtual ~ENode() noexcept {}

                ENGINE  engine;
                ENode * next;
                ENode * prev;
            private:
                Y_Disable_Copy_And_Assign(ENode);
            };

            typedef CxxListOf<ENode> EList;


            template <typename T>
            class Job
            {
            public:
                Y_Args_Declare(T,Type);
                inline Job(Asynchronous &self,
                           ParamType     args) :
                async( self ),
                value( args )
                {
                }

                inline Job(const Job &job) : async(job.async), value(job.value)
                {
                }

                inline ~Job() noexcept {}

                inline void operator()(const Context &ctx)
                {
                    Y_Giant_Lock();
                    (std::cerr << "job @" << ctx << ", value=" << value << std::endl).flush();
                }

                Asynchronous & async;
                Type           value;

            private:
                Y_Disable_Assign(Job);
            };


            inline explicit Asynchronous(const Appliance &app) :
            appliance(app),
            engines()
            {
                upgrade();
            }

            template <typename ARG>
            inline explicit Asynchronous(const Appliance &app, ARG &arg) :
            appliance(app),
            engines()
            {
                upgrade(arg);
            }


            inline virtual ~Asynchronous() noexcept
            {
            }

        protected:
            Appliance      appliance;
            EList          engines;
            
        private:
            Y_Disable_Copy_And_Assign(Asynchronous);
            inline void pre() noexcept {
                while(engines.size>appliance->size()) delete engines.popTail();
            }

            inline void post() noexcept {
                engines.sortByIncreasingAddress();
            }

            inline void upgrade()
            {
                pre();
                while(engines.size<appliance->size()) engines.pushTail( new ENode() );
                post();
            }

            template <typename ARG>
            inline void upgrade(ARG &arg)
            {
                pre();
                while(engines.size<appliance->size()) engines.pushTail( new ENode(arg) );
                post();
            }
        };

    }
}

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


    private:
        Y_Disable_Copy_And_Assign(Engine);
    };
}

Y_UTEST(concurrent_invoke)
{

    Concurrent::Appliance            app = new Concurrent::Queue( Concurrent::Site::Default );
    Concurrent::Asynchronous<Engine> eng( app );

    Concurrent::Asynchronous<Engine>::Job<int>    job1(eng,2);
    Concurrent::Asynchronous<Engine>::Job<String> job2(eng,"Hello");
    Concurrent::Kernel  ker1(job1);
    Concurrent::Kernel  ker2(job2);

    Concurrent::KernelTest::ST(ker1);
    Concurrent::KernelTest::MT(ker2);


}
Y_UDONE()

