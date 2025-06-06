//! \file

#ifndef Y_Memory_Dead_Pool_Included
#define Y_Memory_Dead_Pool_Included 1

#include "y/type/ingress.hpp"
#include "y/memory/page.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/small/guild.hpp"
#include "y/ability/collectable.hpp"

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
        class DeadPool : public Collectable, public Ingress<const Core::LinkedInfo>
        {
        public:
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
            void * query();                            //!< \return a cached/new block
            void   store(void * const zombi) noexcept; //!< store block \param zombi previously acquired
            void   cache(size_t n);                    //!< fast caching new blocks \param n blocks to cache

        private:
            Y_Disable_Copy_And_Assign(DeadPool); //!< discarding
            Y_Ingress_Decl();                    //!< interface
            Core::PoolOf<Page>    zpool;         //!< zombi blocks
            const size_t          bytes;         //!< bytes per block
            Memory::Small::Guild  guild;         //!< memory I/O


        };
    }
}

#endif

