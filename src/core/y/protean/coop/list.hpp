


//! \file

#ifndef Y_Protean_CoopList_Included
#define Y_Protean_CoopList_Included 1

#include "y/protean/proto/list.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/protean/common-container.hpp"

namespace Yttrium
{
    namespace Protean
    {
        //! CONTAINER = Dynamic<Collectable> or Sequence< Dynamic<Collectable> >
        // the cache access is NOT always behind class lock
        template <
        typename NODE,
        typename CONTAINER,
        typename ThreadingPolicy>
        class CoopList : public ListProto<NODE,WarpedCacheOf<NODE,ThreadingPolicy>,CONTAINER,ThreadingPolicy>
        {
        public:
            typedef WarpedCacheOf<NODE,ThreadingPolicy>                PoolType;
            typedef ListProto<NODE,PoolType,CONTAINER,ThreadingPolicy> CoreType;
            using CoreType::pool;
            using CoreType::list;
            typedef typename CoreType::Lock Lock;


            inline virtual ~CoopList() noexcept {}

            inline virtual size_t capacity() const noexcept
            {
                Y_Must_Lock();
                return list.size+pool.count();
            }

            inline virtual size_t available() const noexcept
            {
                Y_Must_Lock();
                return pool.count();
            }

            inline virtual void reserve(const size_t n)
            {
                Y_Must_Lock();
                pool.cache(n);
            }

            inline virtual void free() noexcept
            {
                Y_Must_Lock();
                while(list.size>0)
                    pool.banish( list.popTail() );
            }

            inline virtual void release() noexcept { this->release_(); }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                pool.gc(amount);
            }

        protected:
            inline explicit CoopList(const PoolType &shared) : CoreType(shared) {}
            inline CoopList(const CoopList &other) : Container(), CoreType(other.pool)
            {
                this->duplicate(other);
            }
        private:
            Y_Disable_Assign(CoopList);
        };
    }

}

#endif

