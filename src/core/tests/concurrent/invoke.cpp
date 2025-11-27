
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
            
            class ENode : public Object
            {
            public:
                inline explicit ENode() : Object(), engine() {}
                inline virtual ~ENode() noexcept {}

                ENGINE  engine;
                ENode * next;
                ENode * prev;
            private:
                Y_Disable_Copy_And_Assign(ENode);
            };

            typedef CxxListOf<ENode> EList;


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

}
Y_UDONE()

