
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
                return os;
            }
        }
    }

}


