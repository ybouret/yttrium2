
#include "y/ink/filter/metrics.hpp"
#include "y/calculus/isqrt.hpp"
#include "y/format/decimal.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Ink
    {
        const char * const FilterMetrics :: CallSign = "Ink::FilterMetrics";

        FilterMetrics:: FilterMetrics(const size_t blockSize)   :
        side( IntegerSquareRoot(blockSize) ),
        delta( (side-1) >> 1 )
        {
            if(blockSize<=0)         throw Specific::Exception(CallSign,"no coefficient");
            if(side*side!=blockSize) throw Specific::Exception(CallSign,"%s is not a square", Decimal(blockSize).c_str());
            if(1!=(side&1))          throw Specific::Exception(CallSign,"side=%s is not odd", Decimal(side).c_str());
        }

        FilterMetrics:: ~FilterMetrics() noexcept
        {
        }



    }

}

