//! \file

#ifndef Y_Memory_Book_Included
#define Y_Memory_Book_Included 1


#include "y/memory/limits.hpp"
#include "y/calculus/alignment.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/ability/releasable.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"
#include "y/ability/collectable.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {
            //__________________________________________________________________
            //
            //
            //
            //!  Ledger of pages for Arena/Blocks
            /**
             - contains re-usable pages of different power-of-two size,
             with constraints on sizes.
             - intended for low-level cache
             */
            //
            //
            //__________________________________________________________________
            class Ledger :
            public Singleton<Ledger,BroadLockPolicy>,
            public Collectable
            {
            public:
                //__________________________________________________________________
                //
                //
                // Definitions
                //
                //__________________________________________________________________
                static const char * const CallSign;                                       //!< "Memory::Ledger::Book"
                static const Longevity    LifeTime     = LifeTimeOf:: MemoryObjectLedger; //!< lifetime
                static const unsigned     MinPageShift = Limits::MinBlockShift;           //!< alias
                static const unsigned     MaxPageShift = Limits::MaxBlockShift;           //!< alias
                static const unsigned     NumPageShift = 1+MaxPageShift - MinPageShift;   //!< alias
                static const size_t       MinPageBytes = Limits::MinBlockBytes;           //!< alias
                static const size_t       MaxPageBytes = Limits::MaxBlockBytes;           //!< alias

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void gc(const uint8_t) noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! query clear page
                /**
                 \param blockShift valid block shift
                 \return 2^blockShift bytes
                 */
                void * query(const unsigned blockShift);

                //! store previously queried page
                /**
                 \param blockShift valid block shift
                 \param blockAddr  prevous 2^blockShift page
                 */
                void   store(const unsigned blockShift, void * const blockAddr) noexcept;

                //! reserve pages
                /**
                 \param blockShift valid block shift
                 \param numPages number of 2^blockShift to store
                 */
                void   cache(const unsigned blockShift, const size_t numPages);

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void display(std::ostream &, size_t) const; 

            private:
                Y_Disable_Copy_And_Assign(Ledger);               //!< discarding
                friend class Singleton<Ledger,BroadLockPolicy>;
                explicit Ledger();          //!< initialize
                virtual ~Ledger() noexcept; //!< cleanup


            };
        }
    }

}

#endif

