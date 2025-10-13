

#include "y/mkl/fit/parameter.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {

            Parameter:: ~Parameter() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Parameter &p)
            {
                return os << p.name << "@" << p.indx;
            }

            size_t Parameter:: operator*() const noexcept
            {
                return indx;
            }
        }
    }

}


