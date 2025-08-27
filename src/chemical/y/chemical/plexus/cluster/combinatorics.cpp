
#include "y/chemical/plexus/cluster.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/coven/analysis.hpp"
#include "y/container/ordered/data-book.hpp"
#include "y/container/algorithm/for-each.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        static inline bool KeepComb(const Coven::QVector &v)
        {
            return v.ncof >= 2;
        }
        
        void Cluster:: buildCombinatorics(XMLog &xml)
        {
            static const char fn[] = "Combinatorics";
            Y_XML_Section(xml,fn);

            Coven::Survey comb;
            const iMatrix &Nu = iTopo;
            {
                const iMatrix NuT(TransposeOf,Nu);
                {
                    Coven::Analysis::Run(xml,NuT,KeepComb,comb,Coven::Analysis::RejectRoot,true);
                }
            }

            const size_t         N = elist->size;
            const size_t         M = slist->size;
            CxxArray<apz>        stoi(M);
            DataBook<>::PoolType dpool;

            for(const Coven::QVector *v=comb->head;v;v=v->next)
            {
                const Coven::QVector &coef = *v;
                DataBook<>            inp(dpool);
                Algo::ForEach(stoi, & apz::ldz );
                for(size_t i=1;i<=N;++i)
                {
                    const apz &           cf = coef[i]; if(__Zero__==cf.s) continue;
                    const Readable<int> & nu = Nu[i];
                    for(size_t j=M;j>0;--j)
                    {
                        const int n = nu[j];
                        if(!n) continue;
                        inp |= j;
                        stoi[j] += n * cf;
                    }
                }
                DataBook<> out(dpool);
                for(size_t j=M;j>0;--j) if( stoi[j].s != __Zero__ ) out += j;
                if( !inp.includes(out) ) throw Exception("new indices in output!!");
                const bool       effective = out->size() < inp->size();
                const DataBook<> missing   = inp-out;
                Y_XMLog(xml, (effective ? "[+]" : "[-]") << " stoi=" << stoi << "  #" << inp << "->" << out << " : missing=" << missing << " @" << coef);

            }



        }
    }

}


