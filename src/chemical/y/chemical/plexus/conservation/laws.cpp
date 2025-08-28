

#include "y/chemical/plexus/conservation/laws.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Y_Ingress_Impl(Laws,list)
            
            Laws:: ~Laws() noexcept
            {
            }

            Laws:: Laws(XMLog &        xml,
                        const uMatrix &U,
                        const SList   &slist) :
            Ingress<const Core::ListOf<Law> >(),
            Assembly(),
            list()
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

            }


        }

    }

}

