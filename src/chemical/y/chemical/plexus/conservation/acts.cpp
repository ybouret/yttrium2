
#include "y/chemical/plexus/conservation/acts.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Y_Ingress_Impl(Acts,alist)

            Acts:: ~Acts() noexcept
            {
            }

            Acts:: Acts(XMLog         & xml,
                        const Laws    & laws,
                        const EList   & primary,
                        const iMatrix & topology) :
            Object(), Ingress<const Act::List>(),
            alist()
            {
                const size_t lawCount = laws->size;
                Y_XML_Section_Attr(xml, "Conservation:Acts", Y_XML_Attr(lawCount) );

                for(const Law *law = laws->head; law; law=law->next)
                {
                    if( accepted(*law) ) {
                        tryMerge();
                        continue;
                    }
                    alist.pushTail( new Act(*law) );
                }

                Y_XMLog(xml, "|Acts| = " << alist.size);

                for(Act *act=alist.head;act;act=act->next)
                {
                    const size_t count = (*act)->size();
                    Y_XML_Section_Attr(xml, "Conservation::Act",Y_XML_Attr(count));
                    for(const LNode *ln = (**act)->head;ln;ln=ln->next)
                    {
                        Y_XMLog(xml,**ln);
                    }

                    act->query(primary,topology);
                    Y_XMLog(xml, "elist=" << act->elist);
                    
                }

            }

            bool Acts:: accepted(const Law &law) noexcept
            {
                for(Act *act=alist.head;act;act=act->next)
                {
                    if( act->accepts(law) )
                    {
                        act->connect(law);
                        return true;
                    }
                }
                return false;
            }

            void Acts:: tryMerge() noexcept
            {
                Act::List kept;
                while(alist.size)
                {
                    AutoPtr<Act> rhs = alist.popHead();
                    for(Act *lhs=kept.head;lhs;lhs=lhs->next)
                    {
                        if(lhs->accepts(*rhs))
                        {
                            rhs->combine(*rhs);
                            rhs.free();
                            break;
                        }
                    }
                    if(rhs.isValid()) kept.pushTail( rhs.yield() );
                }
                alist.swapListFor(kept);
            }



        }

    }

}

