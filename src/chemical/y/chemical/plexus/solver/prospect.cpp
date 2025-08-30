#include "y/chemical/plexus/solver/prospect.hpp"
#include <iomanip>

namespace Yttrium
{
    namespace Chemical
    {

        Prospect:: Prospect(const Status        _st,
                            const Equilibrium & _eq,
                            const xreal_t       _eK,
                            XWritable &         _cc,
                            xreal_t             _xi) noexcept :
        st(_st),
        eq(_eq),
        eK(_eK),
        cc(_cc),
        xi(_xi),
        af(0),
        a0(0)
        {
        }

        Prospect:: Prospect(const Prospect &_) noexcept :
        st(_.st),
        eq(_.eq),
        eK(_.eK),
        cc(_.cc),
        xi(_.xi),
        af(_.af),
        a0(_.a0)
        {
        }


        Prospect:: ~Prospect() noexcept
        {
        }

        std::ostream & Prospect:: display(std::ostream &os, const Assembly &fmt) const
        {
            os << Components::HumanReadableStatus(st);
            fmt.display( os << ' ',eq.name, Justify::Right) << ' ';
            os << "@xi=" << std::setw(22) << xi.str();
            //eq.displayCompact(os << ' ',cc,SubLevel);
            return os;
        }

        SignType Prospect:: ByDecreasingXi(const Prospect &lhs, const Prospect &rhs) noexcept
        {
            const xreal_t l = lhs.xi.abs();
            const xreal_t r = rhs.xi.abs();
            return Sign::Of(r,l);
        }

        SignType Prospect:: ByIncreasingAF(const Prospect &lhs, const Prospect &rhs) noexcept
        {
            const xreal_t l = lhs.af;
            const xreal_t r = rhs.af;
            return Sign::Of(l,r);
        }


    }

}
