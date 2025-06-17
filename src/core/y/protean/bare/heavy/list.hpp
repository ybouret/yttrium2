//! \fi;e

#ifndef Y_Protean_BareHeavyLisr_Included
#define Y_Protean_BareHeavyLisr_Included 1

#include "y/protean/node/heavy.hpp"
#include "y/protean/bare/list.hpp"

namespace Yttrium
{
    namespace Protean
    {
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class BareHeavyList : public BareList<HeavyNode<T>,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                       NodeType;
            typedef BareList<NodeType,ThreadingPolicy> BaseType;

            inline explicit BareHeavyList() : BaseType() {}
            inline virtual ~BareHeavyList() noexcept {}
            inline BareHeavyList(const BareHeavyList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(BareHeavyList);
        };

    }

}

#endif
