
//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        
        class Allocator
        {
        protected:
            explicit Allocator(const char * const persistentCallSign) noexcept;

        public:
            virtual ~Allocator() noexcept;

            void * acquire(size_t & blockSize);
            void   release(void * & blockAddr, size_t & blockSize) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Allocator);
            const char * const CallSign_;
            
            //!
            /**
             \param blockSize blockSize>=Align::MinBlockSize
             \return zeroed memory >= blockSize bytes
             */
            virtual void * acquireBlock(size_t &blockSize) = 0;
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept = 0;
        };
    }

}

#endif
