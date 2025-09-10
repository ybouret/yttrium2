
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


            void Court:: trial(XMLog &xml, XWritable &Ctop)
            {
                const size_t count = judges.size;
                if(count)
                {
                    Y_XML_Section_Attr(xml, "Court", Y_XML_Attr(count));
                    for(Judge *judge=judges.head;judge;judge=judge->next)
                    {
                        judge->abide(xml,Ctop);
                        Y_XMLog(xml, "zlist=" << judge->slist);
                    }
                }
            }
        }

    }

}
