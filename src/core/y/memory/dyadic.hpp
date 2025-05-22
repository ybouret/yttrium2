

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
        class Dyadic : public Singleton<Dyadic,GiantLockPolicy>
        {
        public:
            static const char * const CallSign; //!< "Memory::Dyadic"
            static const Longevity    LifeTime      = LifeTimeOf:: DyadicMemory;
            static const size_t       MinBlockBytes = 128;
            static const unsigned     MinBlockShift = IntegerLog2<MinBlockBytes>::Value;
            static const unsigned     MaxBlockShift = Base2<size_t>::MaxShift;
            static const size_t       MaxBlockBytes = Base2<size_t>::MaxValue;

            const uint64_t allocated[MaxBlockShift+1];

        private:
            Y_Disable_Copy_And_Assign(Dyadic);
            friend class Singleton<Dyadic,GiantLockPolicy>;
            
            explicit Dyadic();                 //!< setup
            virtual ~Dyadic() noexcept;        //!< cleanup
            
            virtual void * acquireBlock(size_t & blockSize);
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept;

            void clear() noexcept;
        };

    }

}

#endif

