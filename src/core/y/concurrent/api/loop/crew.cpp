
#include "y/concurrent/api/loop/crew.hpp"
#include "y/concurrent/condition.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/thread.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Crew:: Code : public Object
        {
        public:
            explicit Code(const size_t n) :
            size(n),
            sync(),
            team(size)
            {
                assert(size>0);
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
            }

            inline virtual ~Code() noexcept
            {
                quit();
            }

            const size_t      size;
            Condition         sync;
            CxxSeries<Thread> team;

        private:
            Y_Disable_Copy_And_Assign(Code);

            void loop() noexcept
            {
                Y_Thread_Message("in loop");
            }


            void quit() noexcept
            {
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
