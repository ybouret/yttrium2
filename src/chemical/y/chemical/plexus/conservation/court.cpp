
#include "y/chemical/plexus/conservation/court.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Y_Ingress_Impl(Court,jlist);
            
            Court:: ~Court() noexcept
            {
            }


            Court:: Court(const Clusters &cls) :
            Object(),
            Ingress< const Core::ListOf<Judge> >(),
            jlist()
            {
                for(const Cluster *cl=cls->head;cl;cl=cl->next)
                {
                    if(!cl->canon.isValid()) continue;
                    for(const Act *act = (*cl->canon)->head; act; act=act->next)
                    {
                        jlist.pushTail( new Judge(*act) );
                    }

                }

            }

            void Court:: trial(XMLog &xml, XWritable &Ctop, Accumulator &Itop)
            {
                Y_XML_Section(xml, "Conservation::Court" );
                for(Judge *J=jlist.head;J;J=J->next)
                {
                    J->trial(xml,Ctop,Itop);
                }
            }

            

        }

    }

}
