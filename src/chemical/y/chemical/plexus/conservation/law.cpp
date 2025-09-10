

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/stream/output.hpp"
#include "y/chemical/type/list-ops.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Law:: ~Law() noexcept
            {
            }
            
            Law:: Law() :
            Actors(Actor::InConservation),
            alpha(0),
            lead(),
            zero(0),
            next(0),
            prev(0)
            {
                
            }

            std::ostream & operator<<(std::ostream &os, const Law &law)
            {
                os << "d_(" << law.name << ")";
                return os;
            }


            xreal_t Law:: excess(XAdd &xadd, const XReadable &C, const Level L) const
            {
                xadd.ldz();
                for(const Actor *a = list.head; a; a=a->next)
                {
                    const xreal_t c = a->sp(C,L);
                    for(unsigned n=a->nu;n>0;--n) xadd << c;
                }
                const xreal_t xs = xadd.sum();
                if(xs<zero) return -xs;
                return zero;
            }

            OutputStream & Law:: viz(OutputStream &fp, const String &color) const
            {
                nodeName(fp) << "[";
                fp << "label= < " << html() << " >,color=" << color << ", fontcolor=" << color;
                fp << ",shape=box,style=diagonals";
                Endl(fp<<"]");
                for(const Actor *a=list.head;a;a=a->next)
                {
                    Endl(to( &(a->sp),fp) << "[color=" << color << ",arrowhead=odot]");
                }
                return fp;
            }


            static inline
            size_t CommonSpecies(const Law &law, const Readable<int> &nu) noexcept
            {
                size_t res = 0;
                for(const Actor *a=law->head;a;a=a->next)
                {
                    if( a->sp(nu,SubLevel) ) ++res;
                }
                return res;
            }

            void Law:: queryInvolved(XMLog         &xml,
                                     const EList   &elist,
                                     const iMatrix &itopo)
            {
                const Law &law = *this;
                Y_XML_Section_Attr(xml, "Conservation::Involved", Y_XML_Attr(law));
                for(const ENode *en=elist->head;en;en=en->next)
                {
                    const Equilibrium   &eq = **en;
                    const Readable<int> &nu = itopo[ eq.indx[SubLevel] ];
                    const size_t ncom = CommonSpecies(law,nu);
                    if(CommonSpecies(law,nu)>=2)
                    {
                        Y_XMLog(xml,"[+] " << eq.name << " #" << ncom);
                        Coerce(lead) << eq;
                    }
                }

                ListOps::Make(Coerce(lead),AuxLevel);


            }

        }
    }

}
