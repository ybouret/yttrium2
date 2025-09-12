
#include "y/chemical/plexus/conservation/broken.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Broken:: Broken(const Broken & _) noexcept :
            law(_.law),
            xs(_.xs),
            dc(_.dc)
            {

            }

            Broken:: Broken(const Law & _law, const xreal_t _xs) noexcept :
            law(_law),
            xs(_xs),
            dc(xs/law.norm)
            {
            }

            Broken:: ~Broken() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Broken &broken)
            {
                os << std::setw(22) << broken.dc.str() << " @" << broken.law;
                return os;
            }


            SignType Broken:: Compare(const Broken &lhs, const Broken &rhs) noexcept
            {
                return Sign::Of(lhs.dc,rhs.dc);
            }


            void Broken:: upgrade(Accumulator &Itop) const
            {
                const xreal_t den = law.xa2;
                for(const Actor *a=law->head;a;a=a->next)
                {
                    a->sp(Itop,TopLevel) << (xs * a->xn)/den;
                }
            }

            bool Broken:: still(XAdd &xadd, const XReadable &Ctop) noexcept
            {
                if(( (xs = law.excess(xadd,Ctop,TopLevel)).mantissa > 0 ))
                {
                    dc = xs / law.norm;
                    return true;
                }
                else
                {
                    dc.ldz();
                    return false;
                }
            }


        }

    }

}
