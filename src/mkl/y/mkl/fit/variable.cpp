
#include "y/mkl/fit/variable.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Variable:: ~Variable() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Variable &var)
            {
                return var.display(os);
            }
        }
    }

}


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            PrimaryVariable:: ~PrimaryVariable() noexcept
            {
            }

            std::ostream & PrimaryVariable:: display(std::ostream &os) const
            {
                assert(working==primary);
                return os << name << "@" << primary;
            }

        }
    }

}


namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            ReplicaVariable:: ~ReplicaVariable() noexcept
            {
            }

            std::ostream & ReplicaVariable:: display(std::ostream &os) const
            {
                return os << name << "@" << working << "(-> " << alias << ")";
            }

        }
    }

}
