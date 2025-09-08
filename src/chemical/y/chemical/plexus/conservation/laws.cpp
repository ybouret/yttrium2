

#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {


            Y_Ingress_Impl(Laws,list)
            const char * const Laws:: CSID = "paired10";

            Laws:: ~Laws() noexcept
            {
            }

            Laws:: Laws(XMLog &        xml,
                        const uMatrix &U,
                        const SList   &slist) :
            Ingress<const Core::ListOf<Law> >(),
            Assembly(),
            list(),
            clan(),
            cs( GraphViz::ColorScheme::Query(CSID) )
            {
                assert(U.cols==slist->size);
                const size_t Nc = U.rows;
                const size_t M  = U.cols;
                Y_XML_Section_Attr(xml, "Conservation::Laws", Y_XML_Attr(Nc) << Y_XML_Attr(M));
                for(size_t i=1;i<=Nc;++i)
                {
                    Law & law = * list.pushTail( new Law() );
                    for(size_t j=1;j<=M;++j) {
                        const unsigned cf = U[i][j];
                        if(cf<=0) continue;
                        law.add(cf,**(slist->fetch(j)));
                    }
                    Y_XMLog(xml,law);
                }
                for(const SNode *sn=slist->head;sn;sn=sn->next)
                {
                    const Species &sp = **sn;
                    if(got(sp)) Coerce(clan) << sp;
                }
                Y_XMLog(xml,"species="  << clan);
            }

            bool Laws:: got(const Species &sp) const noexcept
            {
                for(const Law *law=list.head;law;law=law->next)
                {
                    if(law->got(sp)) return true;
                }
                return false;
            }

            OutputStream & Laws:: viz(OutputStream &fp) const
            {
                size_t i=1;
                for(const Law *law=list.head;law;law=law->next,++i)
                {
                    law->viz(fp,cs[i]);
                }
                return fp;
            }


        }

    }

}

