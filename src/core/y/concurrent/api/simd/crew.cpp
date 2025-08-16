
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/condition.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/thread.hpp"
#include "y/type/destroy.hpp"
#include "y/type/temporary.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Crew:: CallSign = "Crew";

#define Y_Print(MSG) do { if(Verbose) { (std::cerr << CallSign << ": " << MSG << std::endl).flush(); } } while(false)

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
            explicit Code(const size_t n) :
            size(n),
            ready(0),
            inUse(0),
            kcode(0),
            mutex(),
            cond(),
            comm(),
            team(size)
            {
                assert(size>0);
                if(Verbose)
                {
                    Y_Lock(mutex);
                    Y_Print("[init] " << size);
                }

                //--------------------------------------------------------------
                //
                // create all threads
                //
                //--------------------------------------------------------------
                try
                {
                    Thread::Proc proc = Launch;
                    void * const args = this;

                    for(size_t i=0;i<size;++i)
                        team.push(proc,args);
                }
                catch(...)
                {
                    quit();
                    throw;
                }

                //--------------------------------------------------------------
                //
                // wait for first synchronization
                //
                //--------------------------------------------------------------
                {
                    Y_Lock(mutex);
                    if(ready<size)
                    {
                        Y_Print("synchronizing...");
                        comm.wait(mutex);
                        Y_Print("...synchronized!");
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
            // execture
            //
            //
            //__________________________________________________________________
            inline void run(Kernel &k) noexcept
            {
                assert(0==kcode);
                const Temporary<Kernel *> tmp(kcode, &k);
                assert(0!=kcode);
                inUse = size;
                cond.broadcast();
                {
                    Y_Lock(mutex);
                    if(inUse>0)
                        comm.wait(mutex);
                }
            }

            const size_t      size;  //!< number of threads
            size_t            ready; //!< ready threads for init/quit
            size_t            inUse; //!< for cycle
            Kernel *          kcode; //!< kernel code
            Mutex             mutex; //!< mutex
            Condition         cond;  //!< threads conditions
            Condition         comm;  //!< communication with primary
            CxxSeries<Thread> team;  //!< local threads

        private:
            Y_Disable_Copy_And_Assign(Code);

            void loop() noexcept
            {
                //--------------------------------------------------------------
                //
                // primary lock and context createion
                //
                //--------------------------------------------------------------
                mutex.lock();
                const Context context(mutex,size,ready++);
                Y_Print(context << " is ready");

                if(ready>=size)
                    comm.broadcast(); // awake primary thread


                //--------------------------------------------------------------
                //
                // wait on a locked mutex
                //
                //--------------------------------------------------------------
            CYCLE:
                cond.wait(mutex);

                //--------------------------------------------------------------
                //
                // wake up on a locked mutex
                //
                //--------------------------------------------------------------
                if(!kcode)
                {
                    Y_Print(context << " done!");
                    assert(ready>0);
                    if(--ready<=0)
                        comm.broadcast(); // awake primary thread
                    mutex.unlock();       // primary unlock
                    return;               // end
                }

                assert(kcode);
                assert(inUse>0);
                Y_Print(context << " is awake");
                mutex.unlock();
                (*kcode)(context);
                mutex.lock();
                assert(inUse>0);
                if(--inUse<=0) comm.broadcast();
                goto CYCLE;
            }


            inline void quit() noexcept
            {
                if(Verbose)
                {
                    Y_Lock(mutex);
                    Y_Print("[quit]");
                }
                kcode = 0;
                cond.broadcast();
                {
                    Y_Lock(mutex);
                    if(ready>0)
                    {
                        Y_Print("[waiting]");
                        comm.wait(mutex);
                    }
                    Y_Print("[done]");
                }

            }

            static void Launch(void * const args)
            {
                assert(args);
                static_cast<Code *>(args)->loop();
            }
        };


        Crew:: Crew(const size_t n) :
        SIMD(n,CallSign),
        code( new Code(n) )
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
            code->run(k);
        }

    }

}
