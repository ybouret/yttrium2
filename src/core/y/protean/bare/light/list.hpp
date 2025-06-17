//! \file

#ifndef Y_Protean_BareLightList_Included
#define Y_Protean_BareLightList_Included 1

#include "y/protean/bare/list.hpp"
#include "y/protean/node/light.hpp"

namespace Yttrium
{
    namespace Protean
    {


        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class BareLightList : public BareList<LightNode<T>,ThreadingPolicy>
        {
        public:
            typedef LightNode<T>                       NodeType;
            typedef BareList<NodeType,ThreadingPolicy> BaseType;
            typedef typename BaseType::Lock            Lock;

            inline explicit BareLightList() : BaseType() {}
            inline virtual ~BareLightList() noexcept {}
            inline BareLightList(const BareLightList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(BareLightList);

        };
    }

}

#endif
