

//! \file

#ifndef Y_Protean_SoloHeavList_Included
#define Y_Protean_SoloHeavytList_Included 1

#include "y/protean/solo/list.hpp"
#include "y/protean/node/heavy.hpp"

namespace Yttrium
{
    namespace Protean
    {

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class SoloHeavyList : public SoloList<HeavyNode<T>,CommonContainer,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                                       NodeType;
            typedef SoloList<NodeType,CommonContainer,ThreadingPolicy> BaseType;

            inline explicit SoloHeavyList() : BaseType() {}
            inline virtual ~SoloHeavyList() noexcept {}
            inline SoloHeavyList(const SoloHeavyList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(SoloHeavyList);

        };
    }

}

#endif
