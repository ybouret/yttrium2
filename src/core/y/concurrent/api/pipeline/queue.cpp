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
            suspend(),
            primary(),
            running(),
            waiting(),
            pending(),
            working(),
            garbage(),
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
            void flush()               noexcept;
            void purge()               noexcept;

            const size_t             size;    //!< team size
            size_t                   ready;   //!< ready counter
            size_t                   built;   //!< built indicator
            Mutex                    mutex;   //!< common mutex
            Condition                suspend; //!< suspend players
            Condition                primary; //!< communication with primary thread
            Players                  running; //!< actually running
            Players                  waiting; //!< actually waiting
            Tasks                    pending; //!< pending tasks
            Tasks                    working; //!< working tasks
            Tasks                    garbage; //!< garbage tasks
            Memory::SchoolOf<Player> team;    //!< memory for players

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
                    primary.wait(mutex);
                    assert(ready==built);
                }
            }

            std::cerr << "all built" << std::endl;
        }

        void Queue:: Coach:: quit() noexcept
        {
            std::cerr << "quit" << std::endl;
            purge();
            suspend.broadcast();

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
            mutex.lock(); // PRIMARY Lock

            //------------------------------------------------------------------
            //
            // setup
            //
            //------------------------------------------------------------------
            const Context ctx(mutex,size,ready);
            Y_Thread_Message("ready=" << ready);
            Player * const player = team.entry + ready;
            waiting.pushTail(player);

            // synchronize with primary thread
            ++ready;
            primary.broadcast();

            // wait on a lock mutex for first loop
        SUSPEND:
            suspend.wait(mutex);

            //------------------------------------------------------------------
            //
            // wake up on a LOCKED mutex
            //
            //------------------------------------------------------------------
            Y_Thread_Message("awaking " << ctx << ", #pending=" << pending.size);
            assert(waiting.owns(player));
            if(pending.size<=0)
            {
                // this is the end...
                goto RETURN;
            }
            else
            {
                //--------------------------------------------------------------
                //
                // change player state
                //
                //--------------------------------------------------------------
                (void) running.pushTail( waiting.pop(player) );
            PERFORM:
                //--------------------------------------------------------------
                //
                // change task state
                //
                //--------------------------------------------------------------
                Task * const task = working.pushTail( pending.popHead() );

                //--------------------------------------------------------------
                //
                // perform unlocked
                //
                //--------------------------------------------------------------

                (void) task;

                //--------------------------------------------------------------
                //
                // locked administrativia
                //
                //--------------------------------------------------------------
                (void) garbage.pushTail( working.pop(task) );

                if(pending.size>0)
                {
                    //----------------------------------------------------------
                    // directly take next job
                    //----------------------------------------------------------
                    Y_Thread_Message("running " << ctx << ", #pending=" << pending.size);
                    goto PERFORM;
                }
                else
                {
                    //----------------------------------------------------------
                    // all done,
                    //----------------------------------------------------------
                    (void) waiting.pushTail( running.pop(player) ); // change player state
                    primary.broadcast();                            // inform primary
                    goto SUSPEND;
                }

            }


        RETURN:
            Y_Thread_Message("leaving " << ctx);
            mutex.unlock(); // PRIMARY UNLOCK
        }

        void Queue::Coach:: enqueue(Task * const task) noexcept
        {
            assert(task);
            Y_Lock(mutex);
            pending.pushTail(task);
            garbage.release();
            if(waiting.size>0)
            {
                suspend.signal();
            }
        }

        void Queue:: Coach:: flush() noexcept
        {
            Y_Lock(mutex);
            if(pending.size>0)
            {
                Y_Thread_Message("flushing...");
                primary.wait(mutex);
            }
            garbage.release();
        }

        void Queue:: Coach:: purge() noexcept
        {
            Y_Lock(mutex);
            pending.release();
            garbage.release();
        }


        const char * const Queue:: CallSign = "Concurrent::Queue";

        Queue:: Queue(const Site site) :
        Pipeline(site->size(),CallSign),
        coach( new Coach(site) )
        {
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


        void Queue:: enqueueTask(Task * const task) noexcept
        {
            assert(task);
            assert(coach);
            coach->enqueue(task);
        }

        void Queue:: flush() noexcept
        {
            assert(coach);
            coach->flush();
        }

        void Queue :: purge() noexcept
        {
            assert(coach);
            coach->purge();
        }

    }

}
