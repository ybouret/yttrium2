#include "y/ink/edge/double-threshold.hpp"
#include "y/format/decimal.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Ink
    {
        DoubleThreshold:: DoubleThreshold(const uint8_t feebleValue,const uint8_t strongValue) noexcept :
        feeble( feebleValue ),
        strong( strongValue )
        {
            assert(feeble<=strong);
        }

        DoubleThreshold:: ~DoubleThreshold() noexcept {}

        DoubleThreshold:: DoubleThreshold(const DoubleThreshold &_) noexcept :
        feeble(_.feeble),
        strong(_.strong)
        {
        }

      

        std::ostream & operator<<(std::ostream &os, const DoubleThreshold &t)
        {
            return os << '[' << Decimal(t.feeble).c_str() << ':' << Decimal(t.strong).c_str() << ']';
        }
    }

}


