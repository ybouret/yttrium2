
//! \file

#ifndef Y_Protean_SoloLightList_Included
#define Y_Protean_SoloLightList_Included 1

#include "y/protean/solo/list.hpp"
#include "y/protean/node/light.hpp"

namespace Yttrium
{
    namespace Protean
    {

        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class SoloLightList : public SoloList<LightNode<T>,CommonContainer,ThreadingPolicy>
        {
        public:
            typedef LightNode<T>                                       NodeType;
            typedef SoloList<NodeType,CommonContainer,ThreadingPolicy> BaseType;
            
            inline explicit SoloLightList() : BaseType() {}
            inline virtual ~SoloLightList() noexcept {}
            inline SoloLightList(const SoloLightList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(SoloLightList);

        };
    }

}

#endif
