

//! \file

#ifndef Y_Protean_CoopLightList_Included
#define Y_Protean_CoopLightList_Included 1

#include "y/protean/coop/list.hpp"
#include "y/protean/node/light.hpp"

namespace Yttrium
{
    namespace Protean
    {

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class CoopLightList : public CoopList<LightNode<T>,CommonContainer,ThreadingPolicy>
        {
        public:
            typedef LightNode<T>                                            NodeType;
            typedef CoopList<NodeType,CommonContainer,ThreadingPolicy>      BaseType;
            typedef typename BaseType::PoolType                             PoolType;

            inline explicit CoopLightList(const PoolType &shared) : BaseType(shared) {}
            inline virtual ~CoopLightList() noexcept {}
            inline CoopLightList(const CoopLightList &other) :
            Container(), BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(CoopLightList);

        };
    }

}

#endif
