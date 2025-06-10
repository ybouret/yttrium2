
#include "y/concurrent/data/dead-pool.hpp"

#include "y/memory/page.hpp"
#include "y/memory/small/guild.hpp"

#include "y/core/utils.hpp"
#include "y/object.hpp"
#include "y/core/linked/pool.hpp"
#include "y/core/linked/list.hpp"
#include "y/core/linked/convert/pool-to-list.hpp"
#include "y/core/linked/convert/list-to-pool.hpp"

#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //! DeadPool
        class DeadPool :: Code : public Object
        {
        public:
            //! setup
            explicit Code(const size_t blockSize) :
            zpool(),
            bytes(0),
            guild( MaxOf<size_t>(blockSize,sizeof(Memory::Page)) )
            {
                Coerce(bytes) = guild.getBlockSize();
            }

            //! cleanup
            virtual ~Code() noexcept
            {
                Y_Lock(*guild);
                while(zpool.size>0)
                    guild.releaseBlock( zpool.query() );
            }


            //! fetch pooled/create memory block
            inline void *conjure()
            {
                return (zpool.size>0)  ? Memory::Page::Addr(zpool.query(),bytes) : guild.acquireBlock();
            }

            //! put into cache
            inline void  prepare(size_t n)
            {
                Y_Lock( *guild );
                while( n-- > 0 )
                    zpool.store( Memory::Page::Cast( guild.acquireBlockUnlocked() ) );
            }


            inline void collect(const uint8_t amount) noexcept
            {
                Core::ListOf<Memory::Page> zlist;
                Core::PoolToList::Convert(zlist,zpool);            // encoding
                zlist.sortByIncreasingAddress();                   // ordering
                const size_t newSize = NewSize(amount,zlist.size); // garbage
                {
                    Y_Lock( *guild );
                    while(zlist.size>newSize)                          //   ...
                        guild.releaseBlockUnlocked( zlist.popTail() ); //   ...
                }
                Core::ListToPool::Convert(zpool,zlist);            // decoding
            }




            Core::PoolOf<Memory::Page> zpool;         //!< zombi blocks
            const size_t               bytes;
            Memory::Small::Guild       guild;         //!< memory I/O

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        DeadPool:: ~DeadPool() noexcept
        {
            assert(0!=code);
            Destroy(code);
        }

        DeadPool:: DeadPool(const size_t userBlockSize) :
        code( new Code(userBlockSize) )
        {
            assert( 0 != code );
        }


        void * DeadPool:: query()
        {
            assert(0!=code);
            return code->conjure();
        }

        void DeadPool:: store(void * const addr) noexcept
        {
            assert(0!=code);
            assert(0!=addr);
            code->zpool.store( Memory::Page::Cast(addr) );
        }

        void DeadPool:: cache(const size_t n)
        {
            assert(0!=code);
            code->prepare(n);
        }

        size_t DeadPool:: count() const noexcept
        {
            assert(0!=code);
            return code->zpool.size;
        }

        void DeadPool:: gc(const uint8_t amount) noexcept
        {
            assert(0!=code);
            code->collect(amount);
        }

        size_t DeadPool:: blockSize()      const noexcept
        {
            assert(0!=code);
            return code->guild.getBlockSize();
        }

    }

}

