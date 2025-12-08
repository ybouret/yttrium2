//! \file

#ifndef Y_Concurrent_Invoke_Included
#define Y_Concurrent_Invoke_Included 1

#include "y/concurrent/api/pipeline.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/cxx/array.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef ArcPtr<Pipeline> Appliance; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Framework to invoke a method on a set of ENGINE linked to threads
        //
        //
        //______________________________________________________________________
        template <typename ENGINE>
        class Invoke
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //__________________________________________________________________
            //
            //
            //! Node containing engine
            //
            //__________________________________________________________________
            class ENode : public Object
            {
            public:
                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                template <typename ARG>
                inline explicit ENode(ARG &arg) : Object(), engine(arg), next(0), prev(0) {} //!< setup \param arg for constructor
                inline explicit ENode()         : Object(), engine()   , next(0), prev(0) {} //!< setup with default constructor
                inline virtual ~ENode() noexcept {} //!< cleanup

                //______________________________________________________________
                //
                // Memberds
                //______________________________________________________________
                ENGINE  engine; //!< instance of ENGINE
                ENode * next;   //!< for list
                ENode * prev;   //!< for list
            private:
                Y_Disable_Copy_And_Assign(ENode); //!< discarding
            };

            typedef CxxListOf<ENode> EList; //!< alias

            //__________________________________________________________________
            //
            //
            //! lightweight Job on a persistent argument
            //
            //__________________________________________________________________
            template <typename T>
            class UnaryJob
            {
            public:
                //______________________________________________________________
                //
                // Definitions
                //______________________________________________________________
                Y_Args_Expose(T,Type);                            //!< aliases
                typedef void (ENGINE::*Meth)(Lockable &, Type &); //!< alias

                //______________________________________________________________
                //
                // C++
                //______________________________________________________________

                //! initialize
                /**
                 \param async where engines are
                 \param which method to inoke
                 \param value persistent value
                 */
                inline UnaryJob(Invoke       &async,
                                Meth const    which,
                                Type &        value) noexcept :
                self(async),
                meth(which),
                args(value)
                {
                }

                //! cleanup
                inline ~UnaryJob() noexcept
                {

                }

                //! duplicate \param job another job
                inline UnaryJob(const UnaryJob &job) noexcept :
                self(job.self),
                meth(job.meth),
                args(job.args)
                {
                }

                //! Kernel behavior \param ctx context of the calling thread
                inline void operator()(const Context &ctx)
                {
                    assert(ctx.indx<=self.meta.size());
                    ENGINE &host = *self.meta[ctx.indx];
                    (host.*meth)(ctx.sync,args);
                }

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                Invoke &   self; //!< engines to invoke
                Meth const meth; //!< method
                Type &     args; //!< argument for method
            };


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param appliance shared pipeline
            inline explicit Invoke(const Appliance &appliance) :
            app(appliance),
            list(),
            meta(app->size())
            {
                setup();
            }

            //! setup \param appliance shared pipeline \param arg argument for ENGINE constructor
            template <typename ARG>
            inline explicit Invoke(const Appliance &appliance, ARG &arg) :
            app(appliance),
            list(),
            meta(app->size())
            {
                setup(arg);
            }

            //! cleanup
            inline virtual ~Invoke() noexcept
            {
                app->flush();
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! invoke same method on different engines
            /**
             \param method  method to invoke
             \param taskIDs populated task identifiers
             \param i       iterator over PERSISTENT arguments
             \param n       number of iterator to scan
             */
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


            //! invoke same method
            /**
             \param method  method to invoke
             \param taskIDs populated task identifiers
             \param seq     sequence of PERSISTENT arguments
             */
            template <typename T, typename SEQUENCE> inline
            void operator()(void      (ENGINE::*method)(Lockable &, T &),
                            TaskIDs  & taskIDs,
                            SEQUENCE & seq)
            {
                (*this)(method,taskIDs,seq.begin(),seq.size());
            }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        protected:
            Appliance           app;  //!< shared pipeline
            EList               list; //!< one engine per pipeline thread
            CxxArray<ENGINE *>  meta; //!< addresses of engines

        private:
            Y_Disable_Copy_And_Assign(Invoke); //!< discarding

            //! post-setup
            inline void post() noexcept
            {
                assert(app->size() == list.size);
                assert(meta.size() == list.size);

                list.sortByIncreasingAddress();
                size_t i=1;
                for(ENode *node=list.head;node;node=node->next,++i)
                    meta[i] = & node->engine;
            }

            //! setup default ENGINES()
            inline void setup()
            {
                const size_t n = app->size();
                while(list.size<n) list.pushTail(new ENode());
                post();
            }

            //! setup \param arg for ENGINES(arg)
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

