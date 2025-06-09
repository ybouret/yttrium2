//! \file

#ifndef Y_Memory_Dead_Pool_Included
#define Y_Memory_Dead_Pool_Included 1

#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! pool of zombified blocks
        //
        //
        //______________________________________________________________________
        class DeadPool : public Caching
        {
        public:
            class Code;
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit DeadPool(const size_t blockSize); //!< setup \param blockSize block size
            virtual ~DeadPool() noexcept;              //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void   gc(const uint8_t) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void *         query();                            //!< \return a cached/new block
            void           store(void * const zombi) noexcept; //!< store block \param zombi previously acquired
            virtual void   cache(const size_t n);              //!< fast caching new blocks \param n blocks to cache
            virtual size_t count() const noexcept;
        private:
            Y_Disable_Copy_And_Assign(DeadPool); //!< discarding
            Code * const code;


        };
    }
}

#endif

