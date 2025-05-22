
//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Interface for memory allocators
        //
        //
        //______________________________________________________________________
        class Allocator
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup
            /** \param persistentCallSign from derived class */
            explicit Allocator(const char * const persistentCallSign) noexcept;

        public:
            //! cleanup
            virtual ~Allocator() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void * acquire(size_t & blockSize);
            void   release(void * & blockAddr, size_t & blockSize) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Allocator); //!< discarding
            const char * const CallSign_;         //!< persistent call sign
            
            //! acquire memory block
            /**
             \param blockSize blockSize>=Align::MinBlockSize
             \return zeroed memory >= blockSize bytes
             */
            virtual void * acquireBlock(size_t &blockSize) = 0;

            //! release memory block
            /**
             \param blockAddr previoulsy acquired address
             \param blockSize its bytes
             */
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept = 0;
        };
    }

}

#endif
