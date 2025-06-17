#include "y/protean/cache/direct.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/utest/run.hpp"


namespace Yttrium
{

  

    namespace Protean
    {
        
        // Bare : releaseable, no cache
        // Solo : recyclable, releaseable, own cache
        // Coop : recyclable, releaseable, shared cache
        
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





}
Y_UDONE()

