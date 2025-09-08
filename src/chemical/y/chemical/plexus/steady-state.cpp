
#include "y/chemical/plexus/steady-state.hpp"
#include "y/chemical/plexus/clusters.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        SteadyState:: SteadyState(const Clusters &cls) :
        sl()
        {
            for(const Cluster *cl=cls->head;cl;cl=cl->next)
                sl.pushTail( new Solver(*cl) );
        }

        SteadyState:: ~SteadyState() noexcept
        {
            
        }

        Y_Ingress_Impl(SteadyState,sl)
        
    }
}
