
#include "y/chemical/plexus/cluster.hpp"
#include "y/mkl/algebra/ortho-space.hpp"
#include "y/coven/analysis.hpp"
#include "y/container/ordered/data-book.hpp"
#include "y/container/algorithm/for-each.hpp"
#include "y/chemical/plexus/cluster/mixed.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        namespace
        {
            static inline bool KeepComb(const Coven::QVector &v)
            {
                return v.ncof >= 2;
            }

            static inline String FirstCoef( const apz &z )
            {
                if(z==1)  return String();
                if(z==-1) return '-';
                return z.str();
            }

            static inline String ExtraCoef( const apz &z )
            {
                if(z==1)  return '+';
                if(z==-1) return '-';
                if(z>1)   return '+' + z.str();
                return z.str();
            }
        }


        void Cluster:: buildCombinatorics(XMLog &xml, Equilibria &eqs, const XReadable &tlK)
        {
            static const char fn[] = "Combinatorics";
            Y_XML_Section(xml,fn);

            const size_t         N = elist->size;
            {
                CxxArray<EList> arr(N);
                Coerce(order).xch(arr);
            }
            for(const ENode *en=elist->head;en;en=en->next)
                Coerce(order[1]) << **en;

            //------------------------------------------------------------------
            //
            //
            // build combination by COVEN
            //
            //
            //------------------------------------------------------------------
            Coven::Survey comb;
            const iMatrix &Nu = iTopo;
            {
                const iMatrix NuT(TransposeOf,Nu);
                {
                    Coven::Analysis::Run(xml,NuT,KeepComb,comb,Coven::Analysis::RejectRoot,true);
                }
            }

            if(comb->size<=0) return;

            //------------------------------------------------------------------
            //
            //
            // Build and keep efficient combination
            //
            //
            //------------------------------------------------------------------
            const size_t         M = slist->size;
            CxxArray<apz>        stoi(M);
            DataBook<>::PoolType dpool;

            for(const Coven::QVector *v=comb->head;v;v=v->next)
            {
                //--------------------------------------------------------------
                //
                // initialize stoi to zero, prepare input indices
                //
                //--------------------------------------------------------------
                const Coven::QVector &coef = *v;
                DataBook<>            inp(dpool);
                Algo::ForEach(stoi, & apz::ldz );

                //--------------------------------------------------------------
                //
                // Compute stoi and fill input indices
                //
                //--------------------------------------------------------------
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

                //--------------------------------------------------------------
                //
                // compute output indices
                //
                //--------------------------------------------------------------
                DataBook<> out(dpool);
                for(size_t j=M;j>0;--j) if( stoi[j].s != __Zero__ ) out += j;
                if( !inp.includes(out) ) throw Exception("new indices in output!!");

                const bool       effective = out->size() < inp->size();
                const DataBook<> missing   = inp-out;
                Y_XMLog(xml, (effective ? "[+]" : "[-]") << " stoi=" << stoi << "  #" << inp << "->" << out << " : missing=" << missing << " @" << coef);
                if(!effective) continue;

                //--------------------------------------------------------------
                //
                // create equilibrium
                //
                //--------------------------------------------------------------

                String eid;
                WList  wl;
                EList  el;
                {
                    bool   first = true;
                    for(size_t i=1;i<=N;++i)
                    {
                        const apz & cf = coef[i]; if(__Zero__==cf.s) continue;
                        if(first)
                        {
                            eid  += FirstCoef(cf);
                            first = false;
                        }
                        else
                            eid += ExtraCoef(cf);
                        Equilibrium &eq = **elist->fetch(i);
                        eid += eq.name;
                        wl << cf.cast<int>("equilibrium weight");
                        el << eq;
                    }
                }
                assert(wl->size == coef.ncof);
                assert(wl->size==el->size);

                MixedEquilibrium &mix = eqs( new MixedEquilibrium(eid,eqs.nextTop(),tlK,wl,el));
                //--------------------------------------------------------------
                //
                // Fill equilibrium
                //
                //--------------------------------------------------------------
                for(size_t j=1;j<=M;++j)
                {
                    const int       cf = stoi[j].cast<int>("stoichio"); if(!cf) continue;
                    const Species & sp = **slist->fetch(j);
                    if(cf>0) mix.p( (unsigned) cf, sp); else mix.r( (unsigned) -cf, sp);
                }
                if(Dangling == mix.flow) throw Specific::Exception(eid.c_str(),"no species!!");
                if(!mix.neutral())       throw Specific::Exception(eid.c_str(),"no neutral!!");
                mix.freeze();

                //--------------------------------------------------------------
                //
                // finalize
                //
                //--------------------------------------------------------------
                elist << mix;
                enroll(mix);
                Coerce(order[coef.ncof]) << mix;
                Y_XMLog(xml, (Components&)mix );
            }

            // update elist sublevel
            ListOps::Make(elist,SubLevel);

          

        }
    }

}


