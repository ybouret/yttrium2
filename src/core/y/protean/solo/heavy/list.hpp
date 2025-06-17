

//! \file

#ifndef Y_Protean_SoloHeavList_Included
#define Y_Protean_SoloHeavytList_Included 1

#include "y/protean/solo/list.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/container/sequence.hpp"

namespace Yttrium
{
    namespace Protean
    {

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class SoloHeavyList : public SoloList<HeavyNode<T>,Sequence<T,CommonContainer>,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                                    NodeType;
            typedef Sequence<T,CommonContainer>                     SequenceType;
            typedef SoloList<NodeType,SequenceType,ThreadingPolicy> BaseType;

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
