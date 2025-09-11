
#include "y/chemical/plexus/conservation/canons.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Y_Ingress_Impl(Acts,clist)

            Acts:: ~Acts() noexcept
            {
            }

            Acts:: Acts(XMLog &xml, const Laws &laws) :
            Object(), Ingress<const Act::List>(),
            clist()
            {
                const size_t count = laws->size;
                Y_XML_Section_Attr(xml, "Conservation:Canons", Y_XML_Attr(count) );

                for(const Law *law = laws->head; law; law=law->next)
                {
                    if(Act *host = accepted(*law))
                    {
                        (void) host;
                        continue;
                    }
                    clist.pushTail( new Act(*law) );
                }
            }

            Act * Acts:: accepted(const Law &law) noexcept
            {
                for(Act *act=clist.head;act;act=act->next)
                {
                    if( act->accepts(law) )
                    {
                        act->connect(law);
                        return act;
                    }
                }
                return 0;
            }


        }

    }

}

