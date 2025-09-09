
#include "y/chemical/plexus/conservation/court.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Y_Ingress_Impl(Court,judges)
            
            Court:: ~Court() noexcept
            {
            }

            Court:: Court(const Clusters &cls) :
            judges()
            {
                for(const Cluster *cl=cls->head;cl;cl=cl->next)
                {
                    if(cl->claws.isValid())
                    {
                        judges.pushTail( new Judge(*cl->claws) );
                    }
                }
            }
        }

    }

}
