
#include "y/chemical/plexus/cluster.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/coven/analysis.hpp"
#include "y/type/momentary.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        static inline bool KeepLaw(const Coven::QVector &v)
        {
            return (v.npos>=2 && v.nneg<=0);
        }

        void Cluster:: buildConservations(XMLog &xml)
        {
            static const char fn[] = "Conservations";
            Y_XML_Section(xml,fn);
            Coven::Survey laws;
            {
                Matrix<apz> Q = MKL::OrthoSpace::Of(iTopo);
                Y_XMLog(xml,"Q=" << Q);
                Y_XMLog(xml,"scanning conservations...");
                const Momentary::Off quiet(xml.verbose);
                Coven::Analysis::Run(xml,Q,KeepLaw,laws,Coven::Analysis::AcceptRoot,true);
            }

            const size_t Nc = laws->size;
            if (Nc<=0)
            {
                Y_XMLog(xml, "no conservation, all species are unbounded.");
                Coerce(unbounded) << slist;
                return;
            }

            const size_t M  = slist->size;
            {
                uMatrix & Q = Coerce(uCLaw).make(Nc,M);
                size_t  i=1;
                for(const Coven::QVector *vec=laws->head;vec;vec=vec->next,++i)
                {
                    vec->sendTo(Q[i],fn);
                }
            }
            Y_XMLog(xml, "uCLaw=" << uCLaw);
            Coerce(claws) = new Conservation::Laws(xml,uCLaw,slist,elist,iTopo);
            Coerce(canon) = new Conservation::Acts(xml,*claws);

            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                const Species &sp = **sn;
                if( claws->got(sp) )
                    Coerce(conserved) << sp;
                else
                    Coerce(unbounded) << sp;
            }
        }
    }

}
