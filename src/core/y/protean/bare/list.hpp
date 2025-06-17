
//! \file

#ifndef Y_Protean_BareList_Included
#define Y_Protean_BareList_Included 1

#include "y/protean/proto/list.hpp"
#include "y/protean/cache/direct.hpp"
#include "y/container.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Protean
    {
        template <
        typename NODE,
        typename ThreadingPolicy>
        class BareList :
        public ListProto<NODE,DirectCacheOf<NODE>,Container,ThreadingPolicy>,
        public Releasable
        {
        public:
            typedef DirectCacheOf<NODE>                                PoolType;
            typedef ListProto<NODE,PoolType,Container,ThreadingPolicy> CoreType;

            inline virtual ~BareList() noexcept {}

            inline virtual void release() noexcept { this->release_(); }

        protected:
            inline explicit BareList() : CoreType(), Releasable() {}
            inline BareList(const BareList &other) : CoreType(), Releasable()
            {
                this->duplicate(other);
            }
        private:
            Y_Disable_Assign(BareList);
        };

    }

}

#endif

