


//! \file

#ifndef Y_Protean_CoopHeavList_Included
#define Y_Protean_CoopHeavList_Included 1

#include "y/protean/coop/list.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/container/sequence.hpp"

namespace Yttrium
{
    namespace Protean
    {

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class CoopHeavyList : public CoopList<HeavyNode<T>,Sequence<T,CommonContainer>,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                                    NodeType;
            typedef Sequence<T,CommonContainer>                     SequenceType;
            typedef CoopList<NodeType,SequenceType,ThreadingPolicy> BaseType;
            typedef typename BaseType::PoolType                     PoolType;

            inline explicit CoopHeavyList(const PoolType &shared) : BaseType(shared) {}
            inline virtual ~CoopHeavyList() noexcept {}
            inline CoopHeavyList(const CoopHeavyList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(CoopHeavyList);

        };
    }

}

#endif
