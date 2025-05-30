
//! \file

#ifndef Y_Memory_Allocator_Included
#define Y_Memory_Allocator_Included 1

#include "y/xml/output.hpp"
#include <cassert>

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

            //! checked aquire
            /**
             - if blockSize>0, it is passed to acquireBlock
             - upon failure, blockSize=0
             \param blockSize desired blockSize
             \return 0 if blockSize==0, valid address otherwise
             */
            void * acquire(size_t & blockSize);

            //! release a previously acquired block
            /**
             works with 0==blockAddr && 0==blockSize
             \param blockAddr address, set to 0
             \param blockSize bytes, set to 0
             */
            void   release(void * & blockAddr, size_t & blockSize) noexcept;

            //! acquire memory for objects
            /**
             \param count minimal count of objects
             \param bytes initially zero, set to acquired
             \return available memory for count objects amd matching bytes
             */
            template <typename T>
            inline T * acquireAs(size_t & count,
                                 size_t & bytes)
            {
                assert(0==bytes);
                if(count>0)
                {
                    try{
                        bytes = count * sizeof(T);
                        T * const entry = static_cast<T *>(acquire(bytes)); assert(bytes>=count*sizeof(T));
                        count = bytes/sizeof(T);
                        return entry;
                    }
                    catch(...)
                    {
                        assert(0==bytes);
                        count = 0;
                        throw;
                    }
                }
                else
                    return 0;
            }



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
