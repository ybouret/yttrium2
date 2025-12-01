
#ifndef Y_Concurrent_Invoke_Included
#define Y_Concurrent_Invoke_Included 1

#include "y/concurrent/api/pipeline.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef ArcPtr<Pipeline> Appliance;

        template <typename ENGINE>
        class Invoke
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

                inline UnaryJob(Invoke       &async,
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
                        //Y_Giant_Lock();
                        //(std::cerr << "job @" << ctx << ", args=" << args << std::endl).flush();
                    }
                    assert(ctx.indx<=self.meta.size());
                    ENGINE &host = *self.meta[ctx.indx];
                    (host.*meth)(ctx.sync,args);
                }

                Invoke & self;
                Meth     meth;
                Type &   args;
            };



            inline explicit Invoke(const Appliance &appliance) :
            app(appliance),
            list(),
            meta(app->size())
            {
                setup();
            }

            template <typename ARG>
            inline explicit Invoke(const Appliance &appliance, ARG &arg) :
            app(appliance),
            list(),
            meta(app->size())
            {
                setup(arg);
            }


            inline virtual ~Invoke() noexcept
            {
                app->flush();
            }


            template <typename T, typename ITERATOR> inline
            void operator()(void      (ENGINE::*method)(Lockable &, T &),
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
            void operator()(void      (ENGINE::*method)(Lockable &, T &),
                            TaskIDs  & taskIDs,
                            SEQUENCE & seq)
            {
                (*this)(method,taskIDs,seq.begin(),seq.size());
            }


        protected:
            Appliance           app;
            EList               list;
            CxxArray<ENGINE *>  meta;

        private:
            Y_Disable_Copy_And_Assign(Invoke);

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

#endif // !Y_Concurrent_Invoke_Included

