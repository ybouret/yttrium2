
#include "y/memory/dead-pool.hpp"
#include "y/core/utils.hpp"
#include "y/core/linked/list.hpp"
#include "y/core/linked/convert/pool-to-list.hpp"
#include "y/core/linked/convert/list-to-pool.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace
        {
            typedef Core::PoolOf<Page> PoolType;
        }

        DeadPool:: ~DeadPool() noexcept
        {
            Y_Lock(*guild);
            while(zpool.size>0)
                guild.releaseBlock( zpool.query() );
        }


        DeadPool:: DeadPool(const size_t blockSize) :
        zpool(),
        bytes(0),
        guild( MaxOf<size_t>(blockSize,sizeof(Page)) )
        {
            Coerce(bytes) = guild.getBlockSize();
        }

        Y_Ingress_Impl(DeadPool,zpool)

        void * DeadPool:: query()
        {
            return zpool.size > 0 ? Page::Addr(zpool.query(),bytes) : guild.acquireBlock();
        }

        void DeadPool:: store(void * const addr) noexcept
        {
            assert(0!=addr);
            zpool.store( Page::Cast(addr) );
        }

        void DeadPool:: cache(size_t n)
        {
            Y_Lock( *guild );
            while( n-- > 0 )
                zpool.store( Page::Cast( guild.acquireBlockUnlocked() ) );
        }

        void DeadPool:: gc(const uint8_t amount) noexcept
        {

            Core::ListOf<Page> zlist;
            Core::PoolToList::Convert(zlist,zpool);            // encoding
            zlist.sortByIncreasingAddress();                   // ordering
            const size_t newSize = NewSize(amount,zlist.size); // garbage
            while(zlist.size>newSize)                          //   ...
                guild.releaseBlock( zlist.popTail() );         //   ...
            Core::ListToPool::Convert(zpool,zlist);            // decoding
        }



    }

}

