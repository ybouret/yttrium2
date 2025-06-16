
#include "y/calculus/safe-add.hpp"
#include "y/system/exception.hpp"
#include "y/decimal.hpp"
#include "y/type/ints.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Calculus
    {
        
        size_t SafeAdd(const size_t lhs, const size_t rhs)
        {
            const size_t Top = IntegerFor<size_t>::Maximum;
            if(rhs>Top-lhs)
                throw Libc::Exception(EDOM,"%s+%s overflow", Decimal(lhs).c_str(), Decimal(rhs).c_str());
            return lhs+rhs;
        }


    }

}
