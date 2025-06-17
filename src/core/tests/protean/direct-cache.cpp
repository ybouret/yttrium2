#include "y/utest/run.hpp"
#include "y/type/args.hpp"

#include "y/memory/small/guild.hpp"
#include "y/type/destruct.hpp"

#include "y/memory/io/zombies.hpp"

#include "y/core/linked/list.hpp"
#include "y/threading/single-threaded-class.hpp"



#include "y/protean/cache/direct.hpp"
#include "y/protean/node/light.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/protean/solo/list.hpp"

namespace Yttrium
{

  

    namespace Protean
    {
        
        // Bare : releaseable, no cache
        // Solo : recyclable, releaseable, own cache
        // Coop : recyclable, releaseable, shared cache








#if 0
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class HeavySoloList : public SoloList<HeavyNode<T>,CommonContainer,ThreadingPolicy>
        {
        public:
            typedef HeavyNode<T>                       NodeType;
            typedef SoloList<NodeType,ThreadingPolicy> BaseType;

            inline explicit HeavySoloList() : BaseType() {}
            inline virtual ~HeavySoloList() noexcept {}
            inline HeavySoloList(const HeavySoloList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(HeavySoloList);
        };
#endif

#if 0
        template <typename T, typename ThreadingPolicy = SingleThreadedClass>
        class LightSoloList : public SoloList<LightNode<T>,ThreadingPolicy>
        {
        public:
            typedef LightNode<T>                       NodeType;
            typedef SoloList<NodeType,ThreadingPolicy> BaseType;

            inline explicit LightSoloList() : BaseType() {}
            inline virtual ~LightSoloList() noexcept {}
            inline LightSoloList(const LightSoloList &other) : BaseType(other)
            {
            }

        private:
            Y_Disable_Assign(LightSoloList);
        };
#endif


    }

}


using namespace Yttrium;



Y_UTEST(protean_direct_cache)
{

    {
        typedef Protean::HeavyNode<int> HNode;
        Protean::DirectCacheOf<HNode> no_cache;
        HNode *node = no_cache.summon(3);
        std::cerr << **node << std::endl;
        HNode *replica = no_cache.mirror(node);
        Y_ASSERT(**replica==**node);
        no_cache.banish(node);
        no_cache.banish(replica);
    }

    int arr[3] = { 1, 2, 3 };
    



}
Y_UDONE()

