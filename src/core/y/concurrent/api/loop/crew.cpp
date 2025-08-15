
#include "y/concurrent/api/loop/crew.hpp"
#include "y/concurrent/condition.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/thread.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Crew:: CallSign = "Crew";

#define Y_Print(MSG) do { if(Verbose) { (std::cerr << CallSign << ": " << MSG << std::endl).flush(); } } while(false)

        class Crew:: Code : public Object
        {
        public:
            explicit Code(const size_t n) :
            size(n),
            ready(0),
            kcode(0),
            mutex(),
            sync(),
            comm(),
            team(size)
            {
                assert(size>0);
                if(Verbose)
                {
                    Y_Lock(mutex);
                    Y_Print("[init] " << size);
                }
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

            inline virtual ~Code() noexcept
            {
                quit();
            }

            const size_t      size;
            size_t            ready;
            void *            kcode;
            Mutex             mutex;
            Condition         sync;
            Condition         comm;
            CxxSeries<Thread> team;

        private:
            Y_Disable_Copy_And_Assign(Code);

            void loop() noexcept
            {
                mutex.lock(); // primary lock
                const size_t rank = ready++;
                Y_Print(size<< '.' << rank << " is ready");

                if(ready>=size)
                {
                    comm.broadcast();
                }

                // wait on a locked mutex
                sync.wait(mutex);

                // wake up on a locked mutex
                if(!kcode)
                {
                    Y_Print(size<< '.' << rank << " done!");
                    assert(ready>0);
                    if(--ready<=0)
                        comm.broadcast();
                    mutex.unlock(); // primary unlock
                    return;         // end
                }
                Y_Print(size<< '.' << rank << " is awake");

            }


            inline void quit() noexcept
            {
                if(Verbose)
                {
                    Y_Lock(mutex);
                    Y_Print("[quit]");
                }
                kcode = 0;
                sync.broadcast();
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
        Loop(n),
        code( new Code(n) )
        {
        }


        Crew:: ~Crew() noexcept
        {
            assert(code);
            Destroy(code);
        }

    }

}
