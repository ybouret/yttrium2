
#include "y/calculus/isqrt.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Calculus
    {
        void IntegerSquareRoot:: throwNegativeArg()
        {
            throw Libc::Exception(EDOM,"negative integer square root argument");
        }
    }
}


