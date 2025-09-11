
#include "y/chemical/plexus/conservation/canons.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Y_Ingress_Impl(Canons,clist)

            Canons:: ~Canons() noexcept
            {
            }

            Canons:: Canons(XMLog &xml, const Laws &laws) :
            Object(), Ingress<const Canon::List>(),
            clist()
            {
                const size_t count = laws->size;
                Y_XML_Section_Attr(xml, "Conservation:Canons", Y_XML_Attr(count) );

                for(const Law *law = laws->head; law; law=law->next)
                {
                    if(Canon *host = accepted(*law))
                    {
                        (void) host;
                        continue;
                    }
                    clist.pushTail( new Canon(*law) );
                }
            }

            Canon * Canons:: accepted(const Law &law) noexcept
            {
                for(Canon *canon=clist.head;canon;canon=canon->next)
                {
                    if( canon->accepts(law) )
                    {
                        canon->connect(law);
                        return canon;
                    }
                }
                return 0;
            }


        }

    }

}

