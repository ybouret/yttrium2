
#include "y/memory/io/zombies.hpp"
#include "y/memory/small/guild.hpp"
#include "y/object.hpp"
#include "y/core/linked/pool.hpp"
#include "y/core/linked/list.hpp"
#include "y/core/linked/convert/list-to-pool.hpp"
#include "y/core/linked/convert/pool-to-list.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Zombies:: Code : public Object
        {
        public:
            inline Code(const size_t userBlockSize) :
            zpool(),
            bytes(0),
            guild(userBlockSize)
            {
                Coerce(bytes) = guild.getBlockSize();
            }

            inline ~Code() noexcept
            {
                Y_Lock(*guild);
                while(zpool.size>0)
                    guild.releaseBlockUnlocked( zpool.query() );
            }

            inline void gc(const uint8_t amount) noexcept
            {
                Core::ListOf<Page> zlist;
                Core::PoolToList::Convert(zlist,zpool);
                zlist.sortByIncreasingAddress();
                {
                    const size_t zsize = Caching::NewSize(amount,zpool.size);
                    Y_Lock( *guild );
                    while(zlist.size>zsize)
                        guild.releaseBlockUnlocked( zlist.popTail() );
                }
                Core::ListToPool::Convert(zpool,zlist);
            }

            inline void * query()
            {
                return (zpool.size>0) ? Page::Addr(zpool.query(),bytes) : guild.acquireBlock();
            }


            Core::PoolOf<Page> zpool;
            const size_t       bytes;
            Small::Guild       guild;


        private:
            Y_Disable_Copy_And_Assign(Code);



        };

        Zombies:: Zombies(const size_t userBlockSize) :
        code( new Code(userBlockSize) )
        {

        }

        Zombies:: ~Zombies() noexcept
        {
            assert(0!=code);
            Destroy(code);
        }

        void Zombies:: gc(const uint8_t amount) noexcept
        {
            assert(0!=code);
            code->gc(amount);
        }

        size_t Zombies:: count() const noexcept
        {
            assert(0!=code);
            return code->zpool.size;
        }

        void Zombies:: cache(const size_t n)
        {
            assert(0!=code);
            Y_Lock(*(code->guild));
            for(size_t i=n;i>0;--i)
                code->zpool.store( Page::Cast( code->guild.acquireBlockUnlocked() ) );
        }

        size_t Zombies:: blockSize() const noexcept
        {
            assert(0!=code);
            return code->bytes;
        }

        void * Zombies:: query()
        {
            assert(0!=code);
            return code->query();
        }

        void  Zombies:: store(void * const addr) noexcept
        {
            assert(0!=code);
            assert(0!=addr);
            code->zpool.store( Page::Cast(addr) );
        }



    }

}

