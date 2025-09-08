

#include "y/chemical/plexus/conservation/law.hpp"
#include "y/stream/output.hpp"

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


        }
    }

}
