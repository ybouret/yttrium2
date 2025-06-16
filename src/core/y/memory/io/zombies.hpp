//! \file

#ifndef Y_Memory_Zombies_Included
#define Y_Memory_Zombies_Included

#include "y/memory/page.hpp"
#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! pool of zombies of same block size
        /**
         - acquisition of new memory is thread-safe
         - query/store of existing blocks is not thread-safe (use limbo)
         */
        //
        //______________________________________________________________________
        class Zombies : public Caching
        {
        public:
            class Code;

            //__________________________________________________________________
            //
            //
            //! C++
            //
            //__________________________________________________________________

            //! setup
            /**
             the internal block size will be set greater than sizeof(Memory::Page)
             \param userBlockSize maximal block size
             */
            explicit Zombies(const size_t userBlockSize);

            //! shared copy
            Zombies(const Zombies &other) noexcept;

            //! cleanup
            virtual ~Zombies() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void   gc(const uint8_t) noexcept;
            virtual size_t count() const noexcept;
            virtual void   cache(const size_t);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            size_t blockSize() const noexcept; //!< \return internal block size

            //! get/create a block \return a used or new block
            void *query();

            //! store previously acquired block
            void  store(void * const) noexcept;

            //! return directly to memory
            void  purge(void * const) noexcept;


        private:
            Y_Disable_Assign(Zombies); //!< discarding
            Code * const code;                  //!< internal code, pool and metricss

        };

    }
}

#endif

