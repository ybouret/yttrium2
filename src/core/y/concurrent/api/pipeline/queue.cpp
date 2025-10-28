#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/type/destroy.hpp"
#include "y/type/destruct.hpp"
#include "y/concurrent/thread.hpp"
#include "y/object/school-of.hpp"
#include "y/concurrent/condition.hpp"
#include "y/core/linked/list/raw.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {

        class Queue:: Player : public Thread
        {
        public:

            inline explicit Player(Proc proc, void * const args) :
            Thread(proc,args),
            next(0),
            prev(0)
            {
                Y_Thread_Message("in player");
            }

            inline virtual ~Player() noexcept {}

            Player *next;
            Player *prev;

        private:
            Y_Disable_Copy_And_Assign(Player);
        };



        class Queue:: Coach : public Object
        {
        public:
            typedef RawListOf<Player> Players;

            inline explicit Coach(const Site &site) :
            size(site->size()),
            ready(0),
            built(0),
            mutex(),
            stop(),
            sync(),
            running(),
            waiting(),
            pending(),
            team(size)
            {
                try { init(); }
                catch(...) { quit(); throw; }

                // localize
                assert(site->size() == built);
                Player * player = team.entry;
                for(const PNode *node= (*site)->head;node;node=node->next,++player)
                {
                    (void) player->assign(**node);
                }
            }

            inline virtual ~Coach() noexcept { quit(); }

            void parallelRun()         noexcept;

            void enqueue(Task * const) noexcept;


            const size_t             size;
            size_t                   ready;
            size_t                   built;
            Mutex                    mutex;
            Condition                stop;
            Condition                sync;
            Players                  running;
            Players                  waiting;
            Tasks                    pending;
            Memory::SchoolOf<Player> team;

        private:
            Y_Disable_Copy_And_Assign(Coach);
            static void Launch(void * const) noexcept;
            void        init();
            void        quit() noexcept;
        };


        void Queue:: Coach:: Launch(void * const args) noexcept
        {
            assert(args);
            static_cast<Coach *>(args)->parallelRun();
        }

        void Queue:: Coach:: init()
        {
            while(built<size)
            {
                new (team.entry+built) Player(Launch,this);
                ++built;
                Y_Lock(mutex);
                if(ready<built)
                {
                    sync.wait(mutex);
                    assert(ready==built);
                }
            }

            std::cerr << "all built" << std::endl;
        }

        void Queue:: Coach:: quit() noexcept
        {
            std::cerr << "quit" << std::endl;
            stop.broadcast();

            while(built>0) {
                Destruct(team.entry+(--built));
            }
        }

        void Queue:: Coach:: parallelRun() noexcept
        {
            //------------------------------------------------------------------
            //
            // entering a new thread
            //
            //------------------------------------------------------------------
            mutex.lock();

            //------------------------------------------------------------------
            //
            // setup
            //
            //------------------------------------------------------------------
            const Context ctx(mutex,size,ready);
            Y_Thread_Message("ready=" << ready);
            Player * const player = team.entry + ready;
            waiting.pushTail(player);

            // synchronize with main thread
            ++ready;
            sync.broadcast();

            // wait on a lock mutex for first loop
            stop.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a locked mutex
            //
            //------------------------------------------------------------------
            {
                Y_Thread_Message("leaving " << ctx);
            }
            mutex.unlock();
        }

        void Queue::Coach:: enqueue(Task * const task) noexcept
        {
            assert(task);
            mutex.lock();
            pending.pushTail(task);
            mutex.unlock();
            
        }



        const char * const Queue:: CallSign = "Concurrent::Queue";

        Queue:: Queue(const Site site) :
        Pipeline(site->size(),CallSign),
        coach( new Coach(site) )
        {
            //std::cerr << "sizeof(Coach)=" << sizeof(Coach) << std::endl;
        }

        Queue:: ~Queue() noexcept
        {
            assert(coach);
            Destroy(coach);
        }

        const char * Queue:: callSign() const noexcept
        {
            return CallSign;
        }


        void Queue:: enqueue(Task * const task) noexcept
        {
            assert(task);
            assert(coach);
            coach->enqueue(task);
        }
    }

}
