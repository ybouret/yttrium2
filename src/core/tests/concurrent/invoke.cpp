
#include "y/concurrent/api/pipeline.hpp"
#include "y/concurrent/api/pipeline/queue.hpp"


#include "y/utest/run.hpp"

#include "y/pointer/arc.hpp"
#include "y/container/cxx/array.hpp"
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
                inline explicit ENode(ARG &arg) : Object(), engine(arg), next(0), prev(0) {}
                inline explicit ENode()         : Object(), engine()   , next(0), prev(0) {}
                inline virtual ~ENode() noexcept {}

                ENGINE  engine;
                ENode * next;
                ENode * prev;
            private:
                Y_Disable_Copy_And_Assign(ENode);
            };

            typedef CxxListOf<ENode> EList;

            //! job on a persistent task
            template <typename T>
            class UnaryJob
            {
            public:
                Y_Args_Expose(T,Type);
                typedef void (ENGINE::*Meth)(Lockable &, Type &);

                inline UnaryJob(Asynchronous &async,
                                Meth const    which,
                                Type &        value) noexcept :
                self(async),
                meth(which),
                args(value)
                {
                }

                inline ~UnaryJob() noexcept
                {

                }

                inline UnaryJob(const UnaryJob &job) noexcept :
                self(job.self),
                meth(job.meth),
                args(job.args)
                {
                }

                //! Kernel behavior
                inline void operator()(const Context &ctx)
                {
                    {
                        Y_Giant_Lock();
                        (std::cerr << "job @" << ctx << ", args=" << args << std::endl).flush();
                    }
                    assert(ctx.indx<=self.meta.size());
                    ENGINE &host = *self.meta[ctx.indx];
                    (host.*meth)(ctx.sync,args);
                }

                Asynchronous & self;
                Meth           meth;
                Type         & args;

            };

            inline explicit Asynchronous(const Appliance &appliance) :
            app(appliance),
            list(),
            meta(app->size())
            {
                setup();
            }

            template <typename ARG>
            inline explicit Asynchronous(const Appliance &appliance, ARG &arg) :
            app(appliance),
            list(),
            meta(app->size())
            {
                setup(arg);
            }


            inline virtual ~Asynchronous() noexcept
            {
                app->flush();
            }


            template <typename T, typename ITERATOR> inline
            void invoke(void      (ENGINE::*method)(Lockable &, T &),
                        TaskIDs & taskIDs,
                        ITERATOR  i,
                        size_t    n)
            {
                assert(method);
                Kernels kernels;
                while(n-- > 0 )
                {
                    const UnaryJob<T> job(*this,method,*(i++));
                    const Kernel      krn(job);
                    kernels << krn;
                }
                app->enqueue(taskIDs,kernels);
            }

            template <typename T, typename SEQUENCE> inline
            void invoke(void      (ENGINE::*method)(Lockable &, T &),
                        TaskIDs  & taskIDs,
                        SEQUENCE & seq)
            {
                invoke(method,taskIDs,seq.begin(),seq.size());
            }






        protected:
            Appliance           app;
            EList               list;
            CxxArray<ENGINE *>  meta;

        private:
            Y_Disable_Copy_And_Assign(Asynchronous);

            inline void post() noexcept
            {
                assert(app->size() == list.size);
                assert(meta.size() == list.size);

                list.sortByIncreasingAddress();
                size_t i=1;
                for(ENode *node=list.head;node;node=node->next,++i)
                    meta[i] = & node->engine;
            }

            inline void setup()
            {
                const size_t n = app->size();
                while(list.size<n) list.pushTail(new ENode());
                post();
            }

            template <typename ARG>
            inline void setup(ARG &arg)
            {
                const size_t n = app->size();
                while(list.size<n) list.pushTail(new ENode(arg));
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

        template <typename T>
        inline void call(Lockable &sync, T & data)
        {
            Y_Lock(sync);
            (std::cerr << "processing (" << data << ")" << std::endl).flush();
        }


    private:
        Y_Disable_Copy_And_Assign(Engine);
    };
}

Y_UTEST(concurrent_invoke)
{

    Concurrent::Appliance            app = new Concurrent::Queue( Concurrent::Site::Default );
    Concurrent::Asynchronous<Engine> eng( app );

    int    iArg = 2;
    String sArg = "Hello";
    Concurrent::Asynchronous<Engine>::UnaryJob<int>    job1(eng, & Engine::call<int>,     iArg);
    Concurrent::Asynchronous<Engine>::UnaryJob<String> job2(eng, & Engine::call<String>,  sArg);
    Concurrent::Kernel  ker1(job1);
    Concurrent::Kernel  ker2(job2);

    Concurrent::KernelTest::ST(ker1);
    Concurrent::KernelTest::MT(ker2);

    Concurrent::TaskIDs taskIDs;
    {
        Vector<int> iVec; iVec << 2 << 3 << 5;
        //eng.invoke(  & Engine::call<int>, taskIDs, iVec.begin(), iVec.size() );
        eng.invoke( &Engine::call<int>, taskIDs, iVec);
        app->flush();
    }




}
Y_UDONE()

