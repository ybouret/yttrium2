

//! \file

#ifndef Y_Memory_Dyadic_Included
#define Y_Memory_Dyadic_Included 1

#include "y/calculus/base2.hpp"
#include "y/calculus/integer-log2.hpp"
#include "y/memory/allocator.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

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
            static const size_t       MinBlockBytes = 128;                               //!< for Chunk with blockSize=1
            static const unsigned     MinBlockShift = IntegerLog2<MinBlockBytes>::Value; //!< alias
            static const unsigned     MaxBlockShift = Base2<size_t>::MaxShift;           //!< alias
            static const size_t       MaxBlockBytes = Base2<size_t>::MaxValue;           //!< alias

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            virtual void display(std::ostream &os) const;

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

