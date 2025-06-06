

//! \file

#ifndef Y_Memory_Dyadic_Included
#define Y_Memory_Dyadic_Included 1

#include "y/memory/limits.hpp"
#include "y/memory/allocator.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/concurrent/singleton/giant-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class System;

        //______________________________________________________________________
        //
        //
        //
        //! Dyadic allocator
        /**
         - calling System::Allocator with power-of-two blocks
         - the possible sizes are limited.
         - this is not a cache
         */
        //
        //
        //______________________________________________________________________
        class Dyadic : public Singleton<Dyadic,GiantLockPolicy>, public Allocator
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Memory::Dyadic"
            static const Longevity    LifeTime      = LifeTimeOf:: DyadicMemory;         //!< lifetime
            static const size_t       MinBlockBytes = Limits::MinBlockBytes;             //!< for Chunk with blockSize=1
            static const unsigned     MinBlockShift = Limits::MinBlockShift;             //!< alias
            static const unsigned     MaxBlockShift = Limits::MaxBlockShift;             //!< alias
            static const size_t       MaxBlockBytes = Limits::MaxBlockBytes;             //!< alias
            static const size_t       ShiftCount    = 1+MaxBlockShift - MinBlockShift;   //!< alias
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            virtual void display(std::ostream &,size_t) const;


            //! unlocked acquire a power-of-two sized block
            /**
             \param blockShift in [MinBlockShift:MaxBlockShift]
             \return a 2^blockShift memory block
             */
            void *       acquireUnlockedDyadic(const unsigned blockShift);


            //! acquire a power-of-two sized block
            /**
             \param blockShift in [MinBlockShift:MaxBlockShift]
             \return a 2^blockShift memory block
             */
            void *       acquireDyadic(const unsigned blockShift);



            //! unlocked release a power-of-two sized block
            /**
             \param blockAddr  previously acquired block
             \param blockShift with 2^blockShift bytes
             */

            void releaseUnlockedDyadic(void * const blockAddr, const unsigned blockShift) noexcept;
            
            //! release a power-of-two sized block
            /**
             \param blockAddr  previously acquired block
             \param blockShift with 2^blockShift bytes
             */
            void releaseDyadic(void * const blockAddr, const unsigned blockShift) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t allocated[MaxBlockShift+1]; //!< number of allocated per blockShift

        private:
            friend class Singleton<Dyadic,GiantLockPolicy>;
            Y_Disable_Copy_And_Assign(Dyadic); //!< discarding
            explicit Dyadic();                 //!< setup
            virtual ~Dyadic() noexcept;        //!< cleanup, display leaks

            virtual void * acquireBlock(size_t & blockSize);
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept;

            void clear() noexcept; //!< reset allocated[]
        };

    }

}

#endif

