
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/condition.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/thread.hpp"
#include "y/type/destroy.hpp"
#include "y/type/temporary.hpp"
#include "y/concurrent/runnable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Crew:: CallSign = "Concurrent::Crew";




        class Crew:: Code : public Object
        {
        public:
            //__________________________________________________________________
            //
            //
            //
            // setup
            //
            //
            //__________________________________________________________________
            explicit Code(const Site &site) :
            size(site->size()),
            ready(0),
            inUse(0),
            kcode(0),
            mutex(),
            barrier(),
            primary(),
            team(size)
            {
                assert(size>0);


                //--------------------------------------------------------------
                //
                // create all threads, synchronized
                //
                //--------------------------------------------------------------
                try
                {
                    Thread::Proc const proc = Run;
                    void * const       args = this;

                    for(size_t i=1;i<=size;++i)
                    {
                        team.push(proc,args);
                        Y_Thread_Suspend_If(ready<i,primary,mutex);
                    }
                    assert(size==ready);
                }
                catch(...)
                {
                    quit();
                    throw;
                }
                

                //--------------------------------------------------------------
                //
                // and localize
                //
                //--------------------------------------------------------------
                {
                    size_t i=1;
                    for(const PNode *node= (*site)->head;node;node=node->next,++i)
                    {
                        team[i].assign(**node);
                    }
                }

            }

            //__________________________________________________________________
            //
            //
            //
            // cleanup
            //
            //
            //__________________________________________________________________
            inline virtual ~Code() noexcept { quit(); }

            //__________________________________________________________________
            //
            //
            //
            // execute kernel
            //
            //
            //__________________________________________________________________
            inline void execute(Kernel &k) noexcept
            {
                assert(0==kcode);
                {
                    const Temporary<Kernel *> tmp(kcode, &k);
                    assert(0!=kcode);
                    inUse = size;
                    barrier.broadcast();
                    Y_Thread_Suspend_If(inUse>0,primary,mutex);
                }
                assert(0==kcode);
            }

            const size_t      size;    //!< number of threads
            size_t            ready;   //!< ready threads for init/quit
            size_t            inUse;   //!< for cycle
            Kernel *          kcode;   //!< kernel code
            Mutex             mutex;   //!< mutex
            Condition         barrier; //!< threads conditions
            Condition         primary; //!< communication with primary
            CxxSeries<Thread> team;    //!< local threads

        private:
            Y_Disable_Copy_And_Assign(Code);

            inline void run() noexcept
            {
                //--------------------------------------------------------------
                //
                // primary lock and context createion
                //
                //--------------------------------------------------------------
                mutex.lock();
                const Context context(mutex,size,ready++);

                // signal primary that we are ready
                primary.signal();


                //--------------------------------------------------------------
                //
                // wait on a locked mutex
                //
                //--------------------------------------------------------------
            CYCLE:
                barrier.wait(mutex);

                //--------------------------------------------------------------
                //
                // wake up on a locked mutex
                //
                //--------------------------------------------------------------
                if(!kcode)
                {
                    assert(ready>0);
                    assert(0==inUse);
                    if(--ready<=0)
                        primary.signal(); // awake primary thread
                    mutex.unlock();       // primary unlock
                    return;               // end of thread
                }

                assert(kcode);
                assert(inUse>0);
                {
                    mutex.unlock();
                    try { (*kcode)(context); } catch(...) {}
                    mutex.lock();
                }
                assert(inUse>0);
                if(--inUse<=0)
                    primary.signal();
                goto CYCLE;
            }


            inline void quit() noexcept
            {
                assert(0==kcode);
                barrier.broadcast();
                Y_Thread_Suspend_If(ready>0,primary,mutex);
            }

            static inline  void Run(void * const args)
            {
                assert(args);
                static_cast<Code *>(args)->run();
            }
        };


        Crew:: Crew(const Site site) :
        SIMD(),
        code( new Code(site) )
        {
        }


        Crew:: ~Crew() noexcept
        {
            assert(code);
            Destroy(code);
        }

        const char * Crew:: callSign() const noexcept
        {
            return CallSign;
        }

        void Crew:: operator()(Kernel &k) noexcept
        {
            assert(code);
            code->execute(k);
        }

        size_t Crew:: size() const noexcept
        {
            return code->size;
        }
        

    }

}
